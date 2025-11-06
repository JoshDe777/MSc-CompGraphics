#pragma once

#include "EisEngine.h"

namespace Maze {
    class Car {
    public:
        explicit Car(Game& game);

        Entity* entity = nullptr;
    };
}
