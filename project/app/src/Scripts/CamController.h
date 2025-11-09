#pragma once

#include <EisEngine.h>

namespace Maze {
    class CamController {
    public:
        explicit CamController(Game& game, Entity* objectToFocus);
    private:
        void Update(Game& game);

        Camera* camera = nullptr;
        Transform* focusTransform = nullptr;
        Game& game;

        float movementSpeed = 0.25f;
        float flyModifier = 20;
        float rotationSpeed = 50;
        float maxRotationDeg = 360;
    };
}
