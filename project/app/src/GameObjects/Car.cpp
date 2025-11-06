#include "Car.h"

namespace Maze {
    Car::Car(Game& game) {
        entity = ResourceManager::Load3DObject(game, "3d-objects/Mercedes_Benz_GLS_580.fbx");

    }
}
