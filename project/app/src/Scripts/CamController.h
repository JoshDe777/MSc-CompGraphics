#pragma once

#include <EisEngine.h>

namespace Maze {
    class CamController {
        using event_t = Event<CamController, CamController&>;
    public:
        explicit CamController(Game& game, const shared_ptr<Entity>& objectToFocus);
        event_t onFocusHold;
    private:
        void Update(Game& game);

        Camera* camera = nullptr;
        Transform* focusTransform = nullptr;

        float movementSpeed = 0.0675f;
        float flyModifier = 20;
        float rotationSpeed = 50;
        float maxRotationDeg = 360;
    };
}
