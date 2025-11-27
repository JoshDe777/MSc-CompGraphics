#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    //steve = make_shared<Steve>(*this);
    //steve->torso->transform->SetLocalPosition(Vector3(0, 0, 0));

    //maze = new ProceduralMaze(*this);

    minotaur = make_shared<Minotaur>(*this);

    camera.transform->SetLocalPosition(Vector3(0, 2, -3));

    controller = make_shared<CamController>(*this, minotaur->entity);
}
