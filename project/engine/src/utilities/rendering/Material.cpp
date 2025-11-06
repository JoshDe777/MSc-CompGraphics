#include "engine/utilities/rendering/Material.h"
#include "engine/utilities/rendering/Shader.h"

namespace EisEngine {
    Material::Material(const Vector3& diffuse, const Vector3 &emission,
                       const float &opacity, const float &metallic,
                       const float &roughness) :
            diffuse(diffuse), emission(emission), opacity(opacity), metallic(metallic), roughness(roughness) {}

    void Material::ApplyMatData(Shader &shader) {
        shader.setVector("diffuse", Color(diffuse, opacity));
    }
}
