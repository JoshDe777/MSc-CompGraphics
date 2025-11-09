#pragma once

#include "engine/utilities/Vector3.h"
#include "engine/utilities/Color.h"

namespace EisEngine {
    namespace rendering{
        class Shader;
    }

    /// \n A class containing an object's material data. Is attached to a Renderer component to apply.
    class Material {
        using Shader = rendering::Shader;
    public:
        /// \n Creates a new Material object from the given data.
        /// @param diffuse - Vector3: The base, lit color/tint for the object.\n
        ///     Defaults to white (255,255,255).
        /// @param emission - Vector3: The color of light emitted by the object in all directions.\n
        ///     Defaults to black (0,0,0) - no light emitted.
        /// @param opacity - float: The object's opacity = inverse transparency.\n
        ///     Defaults to 1 (fully opaque).
        /// @param metallic - float: The degree of metallic property the object has. Correlates with gloss/shininess.\n
        ///     Defaults to 0 (not metallic).
        /// @param roughness - float: The inverse surface uniformity - the rougher the surface, the noisier the lighting effects.\n
        ///     Defaults to 0.5 (semi-matte)
        explicit Material(
                std::string  name,
                const Vector3& diffuse = Vector3(255, 255, 255),
                const Vector3& emission = Vector3::zero,
                const float& opacity = 1,
                const float& metallic = 0,
                const float& roughness = 0.5f
            );

        /// \n Applies material data to the active shader.
        void ApplyMatData(Shader& shader);

        /// \n Prints out the material's values for debugging purposes.
        void Print();

        #pragma region getters
        const Vector3& GetDiffuse() {return diffuse;}
        const Vector3& GetEmission() {return emission;}
        const float& GetOpacity() const {return opacity;}
        const float& GetMetallic() const {return metallic;}
        const float& GetRoughness() const {return roughness;}
        const std::string& Name() {return name;}
        #pragma endregion

        #pragma region setters
        void SetDiffuse(const Vector3& val) {diffuse = val;}
        void SetDiffuse(const Color& val) {diffuse = Vector3(val.r, val.g, val.b);}
        void SetEmission(const Vector3& val) {emission = val;}
        void SetOpacity(const float& val) {opacity = val;}
        void SetMetallic(const float& val) {metallic = val;}
        void SetRoughness(const float& val) {roughness = val;}
        #pragma endregion
    private:
        Vector3 diffuse;
        Vector3 emission;
        float opacity;
        float metallic;
        float roughness;
        std::string name;
    };
}

using Material = EisEngine::Material;
