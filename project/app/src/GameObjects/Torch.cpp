#include "Torch.h"

namespace Maze {
    Torch::Torch(EisEngine::Game &game) {
        entity = static_cast<const shared_ptr<Entity>>(ResourceManager::Load3DObject(game, "3d-objects/own_torch.fbx"));
        entity->transform->SetLocalScale(Vector3(0.0003f, 0.0003f, 0.0003f));
        entity->transform->SetLocalRotation(Vector3(-90, 90, 0));
    }
}
