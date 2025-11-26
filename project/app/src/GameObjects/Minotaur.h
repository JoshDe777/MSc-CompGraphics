#pragma once

#include <EisEngine.h>

namespace Maze {
    class Minotaur {
    public:
        explicit Minotaur(Game& game);
    private:
        Game& game;
        shared_ptr<Entity> entity;
    };
}
