#include "AlgoHandler.h"

#include "DijkstrasAlgorithm.h"

AlgoHandler::AlgoHandler(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) {
    currentSearch = new DijkstrasAlgorithm(grid, canvas, soundPlayer);
}

SearchAlgorithm* AlgoHandler::getCurrentSearch() {
    return currentSearch;
}

void AlgoHandler::setCurrentSearch(SearchAlgorithm* currentSearch) {
    this->currentSearch = currentSearch;
}
