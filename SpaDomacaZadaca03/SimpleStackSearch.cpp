#include "SimpleStackSearch.h"
#include <deque>
#include <algorithm>

void SimpleStackSearch::simpleStackSearch() {
	std::deque<Tile*> stack; // using a deque since std::stack does not support random access
	stack.push_front(startTile);

	while (!stack.empty()) {
		Tile* current = stack.front();
		stack.pop_front();

		std::vector<Tile*> edges = grid.getUncheckedEdges(current);

		if (commonMiddleStep(current)) {
			return;
		}

		for (Tile* edge : edges) {
			if (std::find(stack.begin(), stack.end(), edge) == stack.end()) {
				stack.push_front(edge);
				edge->setParent(current);
			}
		}

		sleep();
	}
}

SimpleStackSearch::SimpleStackSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer) : SearchAlgorithm(grid, canvas, soundPlayer) {}
