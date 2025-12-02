#include "Pathfinding.h"

namespace Maze::AI {
        std::vector<Tile*> Pathfinding::AStarToNode(Tile* start, Tile* target) {
            //GameObject::FindObjectOfType<MapGenerator>()->seaNodes.ResetAllData();
            //start->data.costToNode = 0;
            //start->data.score = Score(start->data.costToNode, start->Heuristic(*target));

            std::vector<Tile*> boundaryNodes = {start};
            bool reachedTarget = false;

            // as long as there is a path available
            while (!boundaryNodes.empty()){
                auto& current = SelectNext(boundaryNodes);          // select new frontier node

                if(current == *target){
                    reachedTarget = true;
                    break;
                }

                //current.data.visited = true;
                boundaryNodes.erase(std::remove(boundaryNodes.begin(), boundaryNodes.end(), &current),
                                    boundaryNodes.end());

                // go through each edge
                /*for(auto e : current.edges){
                    auto neighbor = e->A == &current ? e->B : e->A;

                    if(neighbor->data.visited)
                        continue;

                    // calculate A* score
                    auto costToNext = current.data.costToNode + e->Cost();
                    auto newScore = Score(costToNext, neighbor->Heuristic(*target));

                    if(newScore < neighbor->data.score){
                        neighbor->data.predecessor = &current;
                        neighbor->data.score = newScore;
                        neighbor->data.costToNode = costToNext;

                        if(!ListContains(boundaryNodes, neighbor))
                            boundaryNodes.push_back(neighbor);
                    }
                }*/
            }

            if(!reachedTarget){
                DEBUG_WARN("Could not find valid path.")
                return { };
            }

            std::vector<Tile*> rawPath = {};

            auto current = target;
            while (current != nullptr){
                rawPath.push_back(current);
                //current = current->data.predecessor;
            }

            return rawPath;
        }

    float Pathfinding::Score(const float &costToNode, const float &heuristic) {
        return 0;
    }

    Tile &Pathfinding::SelectNext(const std::vector<Tile *> nodes) {
        return *nodes[0];
    }
}
