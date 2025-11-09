#pragma once

#include <EisEngine.h>

#include "GameObjects/Car.h"
#include "GameObjects/Steve.h"
#include "Scripts/CamController.h"

using namespace Maze;

class MinotaursMaze : public Game {
public:
    explicit MinotaursMaze();
private:
    Car* car = nullptr;
    Steve* steve = nullptr;
    CamController* controller = nullptr;
};
