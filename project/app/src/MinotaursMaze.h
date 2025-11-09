#pragma once

#include <EisEngine.h>

#include "GameObjects/Car.h"
#include "GameObjects/Cube.h"
#include "Scripts/CamController.h"

using namespace Maze;

class MinotaursMaze : public Game {
public:
    explicit MinotaursMaze();
private:
    Car* car = nullptr;
    Cube* cube = nullptr;
    CamController* controller = nullptr;
};
