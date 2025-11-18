#pragma once

#include <EisEngine.h>

namespace Maze {
    class Steve {
    public:
        explicit Steve(Game& game);
        Entity* torso = nullptr;
        void Animate();
    private:
        Entity* neck = nullptr;
        Entity* shoulderL = nullptr;
        Entity* shoulderR = nullptr;
        Entity* hipL = nullptr;
        Entity* hipR = nullptr;

        float animSpeed = 5;
        float stride = 25.0f;
        float moveSpeed = 0.06525f;

        float animTime = 0;
    };
}
