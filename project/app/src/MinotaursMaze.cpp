#include "MinotaursMaze.h"

MinotaursMaze::MinotaursMaze() : Game("Minotaur's Maze") {
    steve = make_shared<Steve>(*this);
    steve->entity->transform->SetLocalPosition(Vector3(0, 0, 0));

    maze = make_shared<ProceduralMaze>(*this);

    minotaur = make_shared<Minotaur>(*this);
    minotaur->entity->transform->SetLocalPosition(Vector3::zero);

    camera.transform->SetLocalPosition(Vector3(0, 2, 0));

    controller = make_shared<CamController>(*this, minotaur->entity);

    RenderingSystem::MarkAsLoader(minotaur->entity.get());
    RenderingSystem::MarkAsLoader(steve->entity.get());
}
