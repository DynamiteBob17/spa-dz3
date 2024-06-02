#include "AStarSearch.h"

void AStarSearch::search() {
    gWeightedQueueSearch(true);
}

long AStarSearch::sleepMin() {
    return 7L;
}

long AStarSearch::sleepMax() {
    return 50L;
}

AStarSearch::AStarSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : GWeightedQueueSearch(grid, canvas, soundPlayer) {}

std::string AStarSearch::getIdentifier() {
    return "A* (A-Star) Search";
}
