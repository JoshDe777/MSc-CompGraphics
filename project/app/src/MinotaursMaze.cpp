#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    /*car = new Car(*this);
    car->entity->transform->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
    car->entity->transform->SetLocalRotation(Vector3(90, 0, 0));
    car->entity->transform->SetLocalPosition(Vector3(0, 0, 0));

    steve = new Steve(*this);
    steve->torso->transform->SetLocalPosition(Vector3(50, 0, 50));*/

    maze = new ProceduralMaze(*this);

    camera.transform->SetLocalPosition(Vector3(0, 2, -3));

    controller = new CamController(*this, maze->env);

    onBeforeShutdown.addListener([&](Game& game){
       // delete car;
       //delete steve;
       delete controller;
       delete maze;
    });
}
