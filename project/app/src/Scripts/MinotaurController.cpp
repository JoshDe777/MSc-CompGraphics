#include "MinotaurController.h"

#include "../GameObjects/Minotaur.h"

namespace Maze::scripts {
    MinotaurController::MinotaurController(
            EisEngine::Game &engine,
            EisEngine::ecs::guid_t owner,
            Maze::Minotaur *minotaur):
            BehaviourTree(engine, owner),
            minotaur(static_cast<std::unique_ptr<Minotaur>>(minotaur)) {

    }

    void MinotaurController::Update() {
        if(deleted)
            return;
        auto rootNode = GetRoot();
        if(!rootNode) {
            DEBUG_RUNTIME_ERROR("Failed to initalize Minotaur AI")
            return;
        }

        rootNode->Evaluate();
    }

    BTNode* MinotaurController::BuildTree() {
        auto* rootNode = new SelectorNode(this, {
                // check for player in attack range. if true swipe at them.
                new SequenceNode(this,{
                        nullptr,nullptr
                        //new CheckForCollisions(this),
                        //new TaskAvoidCollisions(this)
                }),
                // check for line of sight. if true charge at player
                new SequenceNode(this, {
                        nullptr,nullptr
                        //new CheckPlayerInFiringRange(this),
                        //new TaskFireAtPlayer(this)
                }),
                // navigate to player, checking for position
                new SequenceNode(this, {
                        nullptr,nullptr
                        //new CheckPlayerNode(this),
                        //new TaskNavigateToPlayer(this)
                })
        });
        return rootNode;
    }
}