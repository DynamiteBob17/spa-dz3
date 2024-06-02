#pragma once

#include "SearchAlgorithm.h"

class AlgoHandler {
private:
	SearchAlgorithm* currentSearch;
public:
	AlgoHandler(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	SearchAlgorithm* getCurrentSearch();
	void setCurrentSearch(SearchAlgorithm* currentSearch);
};
