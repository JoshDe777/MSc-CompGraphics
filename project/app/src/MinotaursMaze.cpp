#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {

    steve = new Steve(*this);
    steve->torso->transform->SetLocalPosition(Vector3(50, 0, 50));

    //maze = new ProceduralMaze(*this);

    camera.transform->SetLocalPosition(Vector3(0, 2, -3));

    controller = new CamController(*this, steve->torso);

    onBeforeShutdown.addListener([&](Game& game){
       delete steve;
       delete controller;
       //delete cube;
       //delete maze;
    });
}
