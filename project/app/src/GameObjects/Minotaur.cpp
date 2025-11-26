#include "Minotaur.h"

namespace Maze {
    Minotaur::Minotaur(EisEngine::Game &game) : game(game) {
        auto temp = game.entityManager.createEntity("Minotaur");
        entity = static_cast<const shared_ptr<Entity>>(game.entityManager.getEntity(temp.guid()));


    }
}
