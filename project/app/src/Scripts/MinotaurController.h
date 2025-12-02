#pragma once

#include "../MinotaurAI/BehaviourTree/SelectorNode.h"
#include "../MinotaurAI/BehaviourTree/SequenceNode.h"

#include "../MinotaurAI/BehaviourTree/BehaviourTree.h"

namespace Maze {
    class Minotaur;

    namespace scripts {
        using namespace AI;

        class MinotaurController : public BehaviourTree {
        public:
            explicit MinotaurController(Game& engine, guid_t owner, Minotaur* minotaur);
        protected:
            void Update() override;
            BTNode* BuildTree() override;
        private:
            unique_ptr<Minotaur> minotaur;
        };

    }
}
