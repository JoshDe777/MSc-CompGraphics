#include "engine/Game.h"
#include "engine/ResourceManager.h"
#include "engine/Components.h"
#include "engine/utilities/Debug.h"

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace EisEngine {
    std::map<std::string, std::unique_ptr<Texture2D>> ResourceManager::Textures = {};
    std::map<std::string, std::unique_ptr<Material>> ResourceManager::Materials = {};
    std::map<std::string, std::unique_ptr<Shader>> ResourceManager::Shaders = {};
    Assimp::Importer importer;

    /// \n Imports mesh data (vertices, normals, indices and UVs) from an assimp mesh.
    PrimitiveMesh3D ImportMesh(const aiMesh* mesh){
        // vertex collection -> take aiMesh's array of vertices and convert to own format of Vec3's
        std::vector<Vector3> vertices(mesh->mVertices, mesh->mVertices + mesh->mNumVertices);

        // index collection -> iterate through faces & insert the indices for each triangle.
        std::vector<unsigned int> indices = {};
        for(auto i = 0; i < mesh->mNumFaces; i++){
            const auto& face = mesh->mFaces[i];

            // throw an error if not a triangular face.
            assert(face.mNumIndices == 3);
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        // normals collection -> same process as vertex collection
        // (mNormals is always of length mNumVertices, hence the use).
        std::vector<Vector3> normals(mesh->mNormals, mesh->mNormals + mesh->mNumVertices);

        // UV map collection - only collecting from the first channel.
        std::vector<Vector2> uvs;
        uvs.reserve(mesh->mNumVertices);
        if(mesh->HasTextureCoords(0)){
            for(auto i = 0; i < mesh->mNumVertices; i++){
                const auto& uv = mesh->mTextureCoords[0][i];
                uvs.emplace_back(uv);
            }
        }
        else    // if no built-in UVs, give each vertex a texture coord of (0, 0)
            uvs.assign(mesh->mNumVertices, Vector2(0, 0));

        return PrimitiveMesh3D(vertices, indices, normals, uvs);
    }

    /// \n Imports material data from an assimp material.
    Material* ResourceManager::LoadMaterial(const aiMaterial* mat){
        auto matName = std::string(mat->GetName().C_Str());
        if(Materials[matName] == nullptr){
            auto result = *new Material();
            // get properties:
            // -diffuse color AI_MATKEY_COLOR_DIFFUSE
            aiVector3D diffuse;
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
            result.SetDiffuse(Vector3(diffuse));

            // -emission color AI_MATKEY_COLOR_EMISSIVE
            aiVector3D emissive;
            mat->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
            result.SetEmission(Vector3(emissive));

            // -opacity AI_MATKEY_OPACITY
            float opacity;
            mat->Get(AI_MATKEY_OPACITY, opacity);
            result.SetOpacity(opacity);

            // -roughness: no matkey - non-phong attributes obtained with $raw or $mat keys.
            auto roughness = 0.5f;
            if(mat->Get("$raw.Roughness", 0, 0, roughness) != AI_SUCCESS)
                mat->Get("$mat.roughnessFactor", 0, 0, roughness);
            result.SetRoughness(roughness);

            // -metallic: no matkey
            auto metallic = 0.0f;
            if(mat->Get("", 0, 0, metallic) != AI_SUCCESS)
                mat->Get("", 0, 0, metallic);
            result.SetMetallic(metallic);

            // save newly created texture.
            Materials[matName] = make_unique<Material>(result);
        }
        else{
            DEBUG_WARN("Attempting to overwrite existing material " + matName + ".")
        }
        return Materials[matName].get();
    }

    /// \n Imports the texture from a given material.
    Texture2D* ResourceManager::ImportTextureFromAssimp(const aiMaterial* mat, const aiScene* scene) {
        const aiTexture *tex = nullptr;

        // get texture from material. Only embedded textures supported because yeah.
        aiString path;
        mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        // check for embedded texture & error out if not.
        if (path.C_Str()[0] == '*')
            tex = scene->GetEmbeddedTexture(path.C_Str());
        else {
            DEBUG_ERROR("Using external textures is not supported in this engine version!")
            return nullptr;
        }
        auto textureName = std::string(tex->mFilename.C_Str());

        // make sure no duplicate textures.
        if(Textures[textureName] == nullptr){
            // reformat aiTexture data to usable formats.
            auto* dataInCharPtr = reinterpret_cast<unsigned char*>(tex->pcData);
            // stb_image process just like loadFromFile.
            int width, height, nrChannels;
            auto* data = stbi_load_from_memory(dataInCharPtr, tex->mWidth, &width, &height,
                                               &nrChannels, STBI_rgb_alpha);
            if(!data){
                DEBUG_ERROR("Failed to load texture: " + textureName)
                return nullptr;
            }

            auto texture = Texture2D();

            if(nrChannels == 4) {
                texture.internalFormat = GL_RGBA;
                texture.imageFormat = GL_RGBA;
            }

            texture.Generate(width, height, data);
            stbi_image_free(data);

            // Add to texture registry.
            Textures[textureName] = make_unique<Texture2D>(texture);
        }
        else
            DEBUG_WARN("Attempting to overwrite existing texture " + textureName + ".")
        return GetTexture(textureName);
    }

    void ResourceManager::ImportNode(Game& game, const aiNode* node,
                                     const aiScene* scene, const fs::path& modelPath, Entity* parent){
        // if no meshes or children, return
        if(node->mNumMeshes == 0 && node->mNumChildren == 0)
            return;

        // Create entity for node & attach to parent if exists.
        auto nodeEntity = game.entityManager.createEntity(node->mName.C_Str());
        if(parent)
            nodeEntity.transform->SetParent(parent->transform);

        // foreach mesh in node->nMeshes
        for(unsigned int i = 0; i < node->mNumMeshes; i++){

            auto index = node->mMeshes[i];
            auto mesh = scene->mMeshes[index];

            // create submesh entity & attach to node entity.
            auto submesh = &game.entityManager.createEntity(mesh->mName.C_Str());
            submesh->transform->SetParent(nodeEntity.transform);

            // Safety check — skip non-triangular or non-vertex meshes
            if (!mesh->HasPositions() || mesh->mNumVertices == 0)
                continue;

            // get mesh data as primitiveMesh
            auto primitive = ImportMesh(mesh);

            // get texture & material data
            auto assimpMaterial = scene->mMaterials[mesh->mMaterialIndex];
            Material* mat = LoadMaterial(assimpMaterial);
            auto tex = ImportTextureFromAssimp(assimpMaterial, scene);

            // get transform data & update entity transform
            aiVector3D scale, pos;
            aiQuaternion rotation;
            node->mTransformation.Decompose(scale, rotation, pos);
            submesh->transform->SetLocalScale(Vector3(scale));
            Vector3 eulerRotation = Vector3(glm::eulerAngles(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z)));
            submesh->transform->SetLocalRotation(eulerRotation);
            submesh->transform->SetLocalPosition(Vector3(pos));

            // add Mesh3D & Renderer components
            submesh->AddComponent<Mesh3D>(primitive);
            submesh->AddComponent<Renderer>(tex, mat, "");
        }

        // import all child nodes recursively
        for(unsigned int i = 0; i < node->mNumChildren; i++)
            ImportNode(game, node->mChildren[i], scene, modelPath, &nodeEntity);
    }

    ecs::Entity* ResourceManager::Load3DObject(Game& game, const fs::path &path) {
        std::string pathString = path.string();
        // import the asset with a few optimizations for efficiency:
        // meshes triangulated & optimized, normals generated if not exist, and tangents calculated for normals.
        const aiScene* scene = importer.ReadFile(
                pathString.c_str(), aiProcess_Triangulate | aiProcess_GenNormals |
                aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

        // exit with an error message if scene loading failed
        // (scene = nullptr, scene flagged incomplete, or no root node).
        if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
            DEBUG_ERROR("Assimp Error: " + std::string(importer.GetErrorString()))
            return nullptr;
        }

        // recursively import data following the aiScene graph.
        auto& rootEntity = game.entityManager.createEntity(path.filename().string());
        ImportNode(game, scene->mRootNode, scene, path.parent_path(), &rootEntity);

        // return the resulting entity.
        return &rootEntity;
    }

    Texture2D* ResourceManager::GenerateTextureFromFile( const fs::path &imagePath, const std::string &textureName) {
        if(Textures[textureName] == nullptr)
            Textures[textureName] = std::make_unique<Texture2D>(
                    loadTextureFromFile(resolveAssetPath(imagePath)));
        return GetTexture(textureName);
    }

    Texture2D *ResourceManager::GetTexture(const std::string &name) {
        if(Textures.empty()){
            DEBUG_WARN("No textures created in resource manager system.")
            return nullptr;
        }
        return Textures[name].get();
    }

    Texture2D ResourceManager::loadTextureFromFile(const fs::path& filePath) {
        std::string pathString = filePath.string();
        const char* filename = pathString.c_str();
        Texture2D texture;

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

        if(!data){
            DEBUG_ERROR("Failed to load image: " + pathString)
            return texture;
        }

        if(nrChannels == 4) {
            texture.internalFormat = GL_RGBA;
            texture.imageFormat = GL_RGBA;
        }

        texture.Generate(width, height, data);
        
        stbi_image_free(data);

        return texture;
    }

    Shader *ResourceManager::GenerateShaderFromFiles(const fs::path &vertexShaderPath,
                                                     const fs::path &fragmentShaderPath,
                                                     const std::string &shaderName) {
        if(Shaders[shaderName] == nullptr)
            Shaders[shaderName] = std::make_unique<Shader>(
                    loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderPath),
                    loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath)
                    );
        return GetShader(shaderName);
    }

    Shader *ResourceManager::GetShader(const std::string &name) {
        if(Shaders.empty()){
            DEBUG_WARN("No shaders created in resource manager system.")
            return nullptr;
        }
        return Shaders[name].get();
    }

    std::string ResourceManager::ReadText(const fs::path &path) {
        std::ifstream sourceFile(resolveAssetPath(path));
        std::stringstream buffer;
        buffer << sourceFile.rdbuf();
        return buffer.str();
    }

    unsigned int ResourceManager::loadAndCompileShader(GLuint shaderType, const fs::path &filePath) {
        auto shaderID = glCreateShader(shaderType);
        auto shaderSource = ReadText(filePath);
        auto source = shaderSource.c_str();
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        glStatusData compilationStatus{};
        compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
        if(compilationStatus.success == GL_FALSE) {
            glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
            DEBUG_RUNTIME_ERROR( std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
            std::string(compilationStatus.infoLog))
        }

        return shaderID;
    }

    void ResourceManager::Clear(){
        for (auto it = Textures.begin(); it != Textures.end(); ++it)
            glDeleteTextures(1, &it->second->textureID);
    }
}