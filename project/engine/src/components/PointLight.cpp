#include "engine/components/PointLight.h"

#include "engine/ecs/Entity.h"
#include "engine/utilities/rendering/Shader.h"

namespace EisEngine::components {
    PointLight::PointLight(
            Game& game, guid_t owner,
            const Vector3& em,
            const float& I
    ) : Component(game, owner), emission(em), intensity(I) { }

    void PointLight::Apply(rendering::Shader &shader, const int& index) const {
        std::stringstream loc;
        loc.str("");
        loc << "lights[" << index << "].emission";
        shader.setVector(loc.str().c_str(), emission);
        loc.str("");
        loc << "lights[" << index << "].pos";
        shader.setVector(loc.str().c_str(), position());
        loc.str("");
        loc << "lights[" << index << "].I";
        shader.setFloat(loc.str().c_str(), intensity);
    }

    Vector3 PointLight::position() const {
        return entity()->transform->GetGlobalPosition();
    }
}
