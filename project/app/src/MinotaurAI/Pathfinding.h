#pragma once

#include "../MapGeneration/Tile.h"

namespace Maze::AI {
    using namespace Map;

    class Pathfinding {
    public:
        static std::vector<Tile*> AStarToNode(Tile* start, Tile* target);
    private:
        static float Score(const float& costToNode, const float& heuristic);
        static Tile& SelectNext(const std::vector<Tile*> nodes);
    };
}
