#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    car = new Car(*this);
    cube = new Cube(*this);
    camera.transform->SetLocalPosition(car->entity->transform->GetLocalPosition() + Vector3(0, 0, 20));
    DEBUG_LOG("Comparing world positions: Car = " + (std::string) car->entity->transform->GetLocalPosition() +
        "\nCamera: " + (std::string) camera.transform->GetLocalPosition() +
        " - looking at: " + (std::string) -camera.transform->Forward())

    controller = new CamController(*this);

    onBeforeShutdown.addListener([&](Game& game){
       delete car;
       delete cube;
       delete controller;
    });
}
