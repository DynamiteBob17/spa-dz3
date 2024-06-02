#include "GreedyBestFirstSearch.h"

void GreedyBestFirstSearch::search() {
    simpleQueueSearch(true);
}

long GreedyBestFirstSearch::sleepMin() {
    return 15L;
}

long GreedyBestFirstSearch::sleepMax() {
    return 50L;
}

GreedyBestFirstSearch::GreedyBestFirstSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : SimpleQueueSearch(grid, canvas, soundPlayer) {}

std::string GreedyBestFirstSearch::getIdentifier() {
    return "Greedy Best-First Search";
}
