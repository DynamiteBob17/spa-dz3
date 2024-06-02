#pragma once

#include "SearchAlgorithm.h"

class SimpleStackSearch : public SearchAlgorithm {
protected:
	void simpleStackSearch();

public:
	SimpleStackSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
};
