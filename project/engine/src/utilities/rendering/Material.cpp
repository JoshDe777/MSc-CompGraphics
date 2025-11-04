#include "engine/utilities/rendering/Material.h"

namespace EisEngine {
    Material::Material(const Vector3& diffuse, const Vector3 &emission,
                       const float &opacity, const float &metallic,
                       const float &roughness) :
            diffuse(diffuse), emission(emission), opacity(opacity), metallic(metallic), roughness(roughness) {}

    void Material::ApplyTextureDataToShader(Material::Shader &shader) {
        
    }
}
