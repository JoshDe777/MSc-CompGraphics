#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    car = new Car(*this);
    car->entity->transform->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
    car->entity->transform->SetLocalRotation(Vector3(90, 0, 0));
    //steve = new Steve(*this);
    camera.transform->SetLocalPosition(car->entity->transform->GetLocalPosition() + Vector3(0, 0, 5));

    maze = new ProceduralMaze(*this);

    controller = new CamController(*this, car->entity);

    onBeforeShutdown.addListener([&](Game& game){
       delete car;
       //delete steve;
       delete controller;
       delete maze;
    });
}
