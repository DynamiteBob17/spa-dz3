#include "DijkstrasAlgorithm.h"

void DijkstrasAlgorithm::search() {
    gWeightedQueueSearch(false);
}

long DijkstrasAlgorithm::sleepMin() {
    return 3L;
}

long DijkstrasAlgorithm::sleepMax() {
    return 50L;
}

DijkstrasAlgorithm::DijkstrasAlgorithm(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : GWeightedQueueSearch(grid, canvas, soundPlayer) {}

std::string DijkstrasAlgorithm::getIdentifier() {
    return "Dijkstra's Algorithm";
}
