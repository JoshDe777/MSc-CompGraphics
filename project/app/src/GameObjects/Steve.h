#pragma once

#include <EisEngine.h>

namespace Maze {
    class Steve {
    public:
        explicit Steve(Game& game);
        Entity* torso = nullptr;
    private:
        void Animate();
        Entity* neck = nullptr;
        Entity* shoulderL = nullptr;
        Entity* shoulderR = nullptr;
        Entity* hipL = nullptr;
        Entity* hipR = nullptr;

        float animSpeed = 5;
        float stride = 25.0f;
        float moveSpeed = 0.25f;

        float animTime = 0;
    };
}
