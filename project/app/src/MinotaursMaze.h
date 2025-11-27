#pragma once

#include <EisEngine.h>

#include "GameObjects/Steve.h"
#include "GameObjects/Minotaur.h"
#include "Scripts/CamController.h"
#include "MapGeneration/ProceduralMaze.h"

using namespace Maze;
using namespace Maze::Map;

class MinotaursMaze : public Game {
public:
    explicit MinotaursMaze();
private:
    shared_ptr<Steve> steve;
    shared_ptr<CamController> controller;
    shared_ptr<ProceduralMaze> maze = nullptr;
    shared_ptr<Minotaur> minotaur;
};
