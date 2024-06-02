#include "GWeightedQueueSearch.h"

void GWeightedQueueSearch::gWeightedQueueSearch(bool usesHeuristic) {
	auto comparator = [usesHeuristic](Tile* left, Tile* right) {
		if (usesHeuristic) {
			if (left->getFCost() == right->getFCost())
				return left->getHCost() < right->getHCost();
			return left->getFCost() < right->getFCost();
		} else {
			return left->getGCost() < right->getGCost();
		}
		};

	// openSet acts as a priority queue; if in this specific algorithm implementation
	// a PriorityQueue class was used then the search wouldn't work
	// properly since we are adding tiles to the openSet before calculating costs
	// and the PriorityQueue determines the place of the element in the queue upon adding it
	std::vector<Tile*> openSet;
	openSet.push_back(startTile);

	while (!openSet.empty()) {
		auto currentIter = std::min_element(openSet.begin(), openSet.end(), comparator);
		Tile* current = *currentIter;
		openSet.erase(currentIter);

		std::vector<Tile*> edges = grid.getUncheckedEdges(current);

		if (commonMiddleStep(current)) {
			return;
		}

		for (Tile* edge : edges) {
			int totalWeight = current->getGCost() + 1;

			if (std::find(openSet.begin(), openSet.end(), edge) == openSet.end()) {
				openSet.push_back(edge);
			} else if (totalWeight >= edge->getGCost()) {
				continue;
			}

			edge->setGCost(totalWeight);

			if (usesHeuristic) {
				edge->setFCost(edge->getGCost() + edge->getHCost());
			}

			edge->setParent(current);
		}

		sleep();
	}
}

GWeightedQueueSearch::GWeightedQueueSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : SearchAlgorithm(grid, canvas, soundPlayer) {}
