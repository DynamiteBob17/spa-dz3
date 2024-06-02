#pragma once

#include "SearchAlgorithm.h"

class SimpleQueueSearch : public SearchAlgorithm {
protected:
	void simpleQueueSearch(bool usesHeuristic);

public:
	SimpleQueueSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
};
