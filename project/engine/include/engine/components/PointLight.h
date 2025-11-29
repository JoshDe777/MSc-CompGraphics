#pragma once

#include "engine/ecs/Component.h"
#include "engine/utilities/Vector3.h"

namespace EisEngine{
    namespace rendering { class Shader; }

    namespace components {
        using Component = EisEngine::ecs::Component;
        using Shader = EisEngine::rendering::Shader;

        class PointLight : public Component {
        public:
            explicit PointLight (
                    Game& game, guid_t owner,
                    const Vector3& em = Vector3::one,
                    const float& I = 1.0f
            );
            void Apply(Shader& shader, const int& index) const;

            Vector3 GetEmission() const { return emission;}
            float GetIntensity() const {return intensity;}
            Vector3 position() const;

            void SetEmission(const Vector3& v) { emission = v;}
            void SetIntensity(const float& I) { intensity = I;}
        private:
            Vector3 emission;
            float intensity;
        };
    }
}
