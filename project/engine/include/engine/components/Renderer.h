#pragma once

#include "engine/ecs/Component.h"
#include "engine/utilities/rendering/Shader.h"
#include "engine/utilities/rendering/Material.h"
#include "engine/utilities/rendering/Texture2D.h"


namespace EisEngine {
    using ecs::Component;
    using rendering::Shader;

    namespace components {
        /// \n *deprecated* Contains rendering data for any type of mesh.
        /// \n Use specialized renderers tailored to a specific mesh type instead.
        class Renderer : public Component {
        public:
            /// \n Creates a renderer.
            /// @param color - Color: A 4D vector representing a mesh's color in RGBA%.
            /// @param layer - std::string: The rendering layer for meshes paired with a renderer.
            /// \n Currently supported: {"UI" for UI Elements, and [any other string] for regular rendering}.
            Renderer(Game &engine, guid_t owner,
                     Texture2D* tex,
                     Material* mat,
                     std::string  layer = "Background");
            Renderer(const Renderer &renderer) = delete;
            Renderer(Renderer &&other) noexcept;

            /// \n Applies rendering data to the active shader before drawing meshes.
            virtual void ApplyData(Shader& shader);
            /// \n returns a renderer's rendering layer.
            [[nodiscard]] std::string GetLayer() { return m_layer;}

            /// \n Sets a new texture for the corresponding sprite.
            void SetNewTexture(Texture2D* newTexture) {texture = newTexture;}
            /// \n Returns a pointer to the texture assigned to a renderer.
            [[nodiscard]] Texture2D* GetTexture() { return texture;}
        protected:
            /// \n the texture attributed to the associated mesh.
            Texture2D* texture;
            /// \n The material attributed to the associated mesh.
            Material* material;
            /// \n The rendering layer of the associated mesh.
            std::string m_layer;
        };
    }
}
