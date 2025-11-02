#include "engine/components/Renderer.h"

namespace EisEngine::components {
    Renderer::Renderer(EisEngine::Game &engine,
                       EisEngine::ecs::guid_t owner,
                       EisEngine::Texture2D *tex,
                       EisEngine::Material *mat, std::string layer) :
                       Component(engine, owner),
                       texture(tex),
                       material(mat),
                       m_layer(std::move(layer)) { }

    Renderer::Renderer(EisEngine::components::Renderer &&other) noexcept :
            Component(other) {
        owner = other.owner;
        std::swap(this->texture, other.texture);
        std::swap(this->material, other.material);
        std::swap(this->m_layer, other.m_layer);
    }

    // applies the selected color to the active shader.
    void Renderer::ApplyData(Shader& shader) {
        material->ApplyTextureDataToShader(shader);

        if(!texture)
            return;

        Shader::ApplyTexture(*texture);
    }

    void Renderer::Invalidate() {
        delete material;
        material = nullptr;
        Component::Invalidate();
    }
}