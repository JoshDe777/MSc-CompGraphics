#include "Cube.h"

namespace Maze {
    Cube::Cube(Game& game) {
        entity = &game.entityManager.createEntity("Cube");
        entity->AddComponent<Mesh3D>(PrimitiveMesh3D::cube);
        entity->AddComponent<Renderer>(nullptr, nullptr);
        entity->transform->SetLocalPosition(Vector3::zero);
    }
}
