#include "DepthFirstSearch.h"

void DepthFirstSearch::search() {
    simpleStackSearch();
}

long DepthFirstSearch::sleepMin() {
    return 15L;
}

long DepthFirstSearch::sleepMax() {
    return 50L;
}

DepthFirstSearch::DepthFirstSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : SimpleStackSearch(grid, canvas, soundPlayer) {}

std::string DepthFirstSearch::getIdentifier() {
    return "DFS (Depth-First Search)";
}
