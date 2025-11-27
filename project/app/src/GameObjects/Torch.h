#pragma once

#include <EisEngine.h>

namespace Maze {
    class Torch {
    public:
        explicit Torch(Game& game);
        shared_ptr<Entity> entity = nullptr;
    };
}
