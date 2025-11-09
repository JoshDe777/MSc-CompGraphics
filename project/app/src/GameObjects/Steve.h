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
    };
}
