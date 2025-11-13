#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    //car = new Car(*this);
    //car->entity->transform->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
    //car->entity->transform->SetLocalRotation(Vector3(90, 0, 0));
    steve = new Steve(*this);

    maze = new ProceduralMaze(*this);

    camera.transform->SetLocalPosition(maze->env->transform->GetLocalPosition() + Vector3(0, 2, 0));

    controller = new CamController(*this, steve->torso);

    onBeforeShutdown.addListener([&](Game& game){
       //delete car;
       delete steve;
       delete controller;
       delete maze;
    });
}
