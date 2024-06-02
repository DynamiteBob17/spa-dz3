#include "SimpleQueueSearch.h"
#include <deque>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <functional>

void SimpleQueueSearch::simpleQueueSearch(bool usesHeuristic) {
    using TilePtr = Tile*;
    std::queue<TilePtr> queue;
    std::priority_queue<TilePtr, std::vector<TilePtr>, std::function<bool(TilePtr, TilePtr)>> priorityQueue(
        [](TilePtr left, TilePtr right) { return left->getHCost() > right->getHCost(); }
    );

    std::unordered_set<TilePtr> visited;

    if (usesHeuristic) {
        priorityQueue.push(startTile);
    }
    else {
        queue.push(startTile);
    }
    visited.insert(startTile);

    while (usesHeuristic ? !priorityQueue.empty() : !queue.empty()) {
        Tile* current = usesHeuristic ? priorityQueue.top() : queue.front();

        if (usesHeuristic) {
            priorityQueue.pop();
        } else {
            queue.pop();
        }

        std::vector<Tile*> edges = grid.getUncheckedEdges(current);

        if (commonMiddleStep(current)) {
            return;
        }

        for (Tile* edge : edges) {
            if (visited.find(edge) == visited.end()) {
                if (usesHeuristic) {
                    priorityQueue.push(edge);
                }
                else {
                    queue.push(edge);
                }
                edge->setParent(current);
                visited.insert(edge);
            }
        }

        sleep();
    }
}

SimpleQueueSearch::SimpleQueueSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : SearchAlgorithm(grid, canvas, soundPlayer) {}
