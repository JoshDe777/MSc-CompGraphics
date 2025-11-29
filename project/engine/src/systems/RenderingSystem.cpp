#include "engine/systems/RenderingSystem.h"
#include "engine/Game.h"
#include "engine/Components.h"

// DO NOT UPDATE WITHOUT ALSO UPDATING SAME NAMED MACRO IN FRAGMENT SHADERS!
#define MAX_LIGHTS 25
#define INTENSITY_THRESHOLD (1.0f/9.0f)
#define MIN_DIST 0.1f

namespace EisEngine::systems {
// helper functions:

    // used to sort entities by ascending z position.
    bool CompareZValues(SpriteMesh* a, SpriteMesh* b)
    { return a->entity()->transform->GetGlobalPosition().z < b->entity()->transform->GetGlobalPosition().z;}

// rendering system methods:

    RenderingSystem::RenderingSystem(EisEngine::Game &engine) : System(engine) {
        camera = &engine.camera;
        if(!camera)
            DEBUG_RUNTIME_ERROR("Cannot initialize rendering; Camera not found.")

        engine.onUpdate.addListener([&] (Game& engine){ Draw();});

        VAO = {};
        for(unsigned int & i : VAO)
            glGenVertexArrays(1, &i);

        // generate default shader (mesh2D & lines)
        ResourceManager::GenerateShaderFromFiles("shaders/vertexShader.vert",
                                                 "shaders/fragmentShader.frag",
                                                 "Default Shader");
        // generate default sprite shader
        ResourceManager::GenerateShaderFromFiles( "shaders/betterVertexShader.vert",
                                                  "shaders/spriteFragmentShader.frag",
                                                  "Sprite Shader");
        // generate ui sprite shader
        ResourceManager::GenerateShaderFromFiles("shaders/betterVertexShader.vert",
                                                 "shaders/spriteFragmentShader.frag",
                                                 "UI Shader");
        // generate 3D shader
        ResourceManager::GenerateShaderFromFiles("shaders/betterVertexShader.vert",
                                                 "shaders/fragmentShader3D.frag",
                                                 "3D Shader");
    }

    void RenderingSystem::Draw() {
        // re-enable depth testing for 'regular' entities.
        glEnable(GL_DEPTH_TEST);
        auto i = 0;

        #pragma region Default Shader
        auto activeShader = ResourceManager::GetShader("Default Shader");

        // Mesh2D rendering
        if(engine.componentManager.hasComponentOfType<Mesh2D>()){
            glBindVertexArray(VAO[i++]);
            activeShader->Apply(camera);
            engine.componentManager.forEachComponent<Mesh2D>([&](Mesh2D& mesh){
                auto model = mesh.entity()->transform->GetModelMatrix();
                activeShader->setMatrix("mvp", activeShader->CalculateMVPMatrix(model));
                auto renderer = mesh.entity()->GetComponent<Renderer>();
                if(renderer)
                    renderer->ApplyData(*activeShader);
                mesh.draw();
            });
        }

        // line rendering (same shader as Mesh2D's)
        if(engine.componentManager.hasComponentOfType<Line>()){
            glBindVertexArray(VAO[i++]);
            engine.componentManager.forEachComponent<Line>([&] (Line& mesh){
                auto renderer = mesh.entity()->GetComponent<Renderer>();
                if(renderer)
                    renderer->ApplyData(*activeShader);
                auto model = mesh.entity()->transform->GetModelMatrix();
                activeShader->setMatrix("mvp", activeShader->CalculateMVPMatrix(model));
                mesh.draw();
            });
        }
        #pragma endregion

        #pragma region 3D rendering
        // Mesh3D rendering
        activeShader = ResourceManager::GetShader("3D Shader");
        if(engine.componentManager.hasComponentOfType<Mesh3D>()){
            glBindVertexArray(VAO[i++]);
            activeShader->Apply(camera);
            engine.componentManager.forEachComponent<Mesh3D>([&](Mesh3D& mesh){
                auto model = mesh.entity()->transform->GetModelMatrix();
                activeShader->setMatrix("mvp", activeShader->CalculateMVPMatrix(model));auto normalMat = glm::mat3(model);
                // if mat is inversible, apply inverse transposed matrix
                if(abs(glm::determinant(normalMat)) >= 1e-6f)
                    normalMat = glm::transpose(glm::inverse(glm::mat3(model)));
                else {
                    // normalize matrix to kill scale variance
                    normalMat[0] = glm::normalize(normalMat[0]);
                    normalMat[1] = glm::normalize(normalMat[1]);
                    normalMat[2] = glm::normalize(normalMat[2]);
                }
                activeShader->setMatrix("normalMat", normalMat);
                auto renderer = mesh.entity()->GetComponent<Renderer>();
                if(renderer)
                    renderer->ApplyData(*activeShader);

                // get lights
                std::vector<PointLight*> lights = {};
                auto pos = mesh.entity()->transform->GetGlobalPosition();
                double furthestLight = 10000000000000000000.0;
                if(engine.componentManager.hasComponentOfType<PointLight>()){
                    // get list of MAX_LIGHTS closest light sources to object with
                    // an illumination (I / dist^2) reaching above the threshold.
                    engine.componentManager.forEachComponent<PointLight>([&](PointLight& light){
                        auto dist = Vector3::Distance(light.position(), pos);
                        if(
                            // to avoid light sources affecting themselves
                            dist >= MIN_DIST &&
                            light.GetIntensity() / (dist*dist) > INTENSITY_THRESHOLD &&
                            // either closer than the furthest light in list or if less than max lights considered.
                            (dist < furthestLight || lights.size() < MAX_LIGHTS)
                        ){
                            float largestDist = dist;
                            // insert at right place
                            if(lights.empty())
                                lights.push_back(&light);
                            else{
                                for(int i = (int) lights.size() - 1; i >= 0; i--){
                                    auto nDist = Vector3::Distance(lights[i]->position(), pos);
                                    largestDist = max(largestDist, nDist);
                                    if(dist < nDist)
                                       continue;

                                    // dist >= nDist
                                    lights.insert(lights.begin() + i + 1, &light);
                                    // keep max lights count
                                    if(lights.size() > MAX_LIGHTS)
                                        lights.pop_back();
                                    break;
                                }
                            }
                            furthestLight = (double) largestDist;
                        }
                    });
                }

                for(auto i = 0; i < lights.size(); i++)
                    lights[i]->Apply(*activeShader, i);
                activeShader->setInt("nLights", (int) lights.size());

                mesh.draw(activeShader->GetShaderID());
            });
        }
        #pragma endregion

        #pragma region Sprite Rendering
        activeShader = ResourceManager::GetShader("Sprite Shader");

        // Sprite rendering

        // weed out UI Sprites for later overlay rendering
        std::vector<SpriteMesh*> uiSprites = {};

        if(engine.componentManager.hasComponentOfType<SpriteMesh>()){
            glBindVertexArray(VAO[i++]);
            activeShader->Apply(camera);
            engine.componentManager.forEachComponent<SpriteMesh>([&] (SpriteMesh& mesh){
                auto renderer = mesh.entity()->GetComponent<Renderer>();
                if(!renderer){
                    DEBUG_ERROR("No sprite renderer attached to mesh on entity " + mesh.entity()->name())
                    return;
                }
                if(renderer->GetLayer() == "UI"){
                    uiSprites.emplace_back(&mesh);
                    return;
                }
                renderer->ApplyData(*activeShader);
                auto model = mesh.entity()->transform->GetModelMatrix();
                activeShader->setMatrix("mvp", activeShader->CalculateMVPMatrix(model));
                mesh.draw();
            });
        }

        // return if no UI sprites to render
        if(uiSprites.empty())
            return;

        // disable depth testing here for UI
        glDisable(GL_DEPTH_TEST);

        // sort by ascending z values for layering because no depth test.
        std::sort(uiSprites.begin(), uiSprites.end(), CompareZValues);

        activeShader = ResourceManager::GetShader("UI Shader");

        glBindVertexArray(VAO[i++]);
        activeShader->Apply(camera);
        for (auto mesh : uiSprites) {
            auto renderer = mesh->entity()->GetComponent<Renderer>();
            renderer->ApplyData(*activeShader);
            auto screenWidth = camera->GetWidth();
            auto screenHeight = camera->GetHeight();
            auto projection = glm::ortho(-(float) screenWidth / 2, (float) screenWidth / 2,
                                         - (float) screenHeight / 2, (float) screenHeight / 2);
            auto modelProjection = projection * mesh->entity()->transform->GetModelMatrix();
            activeShader->setMatrix("mvp", modelProjection);
            mesh->draw();
        }
        #pragma endregion
    }
}
