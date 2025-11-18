#pragma once

#include <EisEngine.h>

#include "GameObjects/Car.h"
#include "GameObjects/Steve.h"
#include "Scripts/CamController.h"
#include "MapGeneration/ProceduralMaze.h"
#include "GameObjects/Cube.h"

using namespace Maze;
using namespace Maze::Map;

class MinotaursMaze : public Game {
public:
    explicit MinotaursMaze();
private:
    Cube* cube = nullptr;
    Car* car = nullptr;
    Steve* steve = nullptr;
    CamController* controller = nullptr;
    ProceduralMaze* maze = nullptr;
};
