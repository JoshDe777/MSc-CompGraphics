#pragma once

#include <EisEngine.h>

namespace Maze {
    class CamController {
    public:
        explicit CamController(Game& game);
    private:
        void Update(Game& game);

        Camera* camera = nullptr;
        float movementSpeed = 1;
    };
}
