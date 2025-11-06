#include "MinotaursMaze.h"
#include "GameObjects/Car.h"
#include "GameObjects/Cube.h"
#include "Scripts/CamController.h"

using namespace Maze;

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    //Car* car = new Car(*this);
    Cube* cube = new Cube(*this);
    camera.transform->SetLocalPosition(cube->entity->transform->GetLocalPosition() + Vector3(0, 0, 5));
    /*DEBUG_LOG("Comparing world positions: Car = " + (std::string) car->entity->transform->GetLocalPosition() +
        "\nCamera: " + (std::string) camera.transform->GetLocalPosition() +
        " - looking at: " + (std::string) camera.transform->Forward())*/

    auto* controller = new CamController(*this);

    onBeforeShutdown.addListener([&](Game& game){
       //delete car;
       delete cube;
       delete controller;
    });
}
