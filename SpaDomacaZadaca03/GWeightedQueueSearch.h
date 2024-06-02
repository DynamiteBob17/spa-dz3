#pragma once

#include "SearchAlgorithm.h"

class GWeightedQueueSearch : public SearchAlgorithm {
protected:
	void gWeightedQueueSearch(bool usesHeuristic);

public:
	GWeightedQueueSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
};
