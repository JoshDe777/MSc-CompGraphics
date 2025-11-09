#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    //car = new Car(*this);
    steve = new Steve(*this);
    camera.transform->SetLocalPosition(steve->torso->transform->GetLocalPosition() + Vector3(0, 0, 5));

    controller = new CamController(*this, steve->torso);

    onBeforeShutdown.addListener([&](Game& game){
       //delete car;
       delete steve;
       delete controller;
    });
}
