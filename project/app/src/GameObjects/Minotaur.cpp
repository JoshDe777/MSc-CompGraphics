#include "Minotaur.h"

namespace Maze {
    Minotaur::Minotaur(EisEngine::Game &game) : game(game) {
        entity = static_cast<const shared_ptr<Entity>>(ResourceManager::Load3DObject(game, "3d-objects/minotaur.fbx"));
        entity->transform->SetLocalScale(Vector3(0.1f, 0.1f, 0.1f));
    }
}
