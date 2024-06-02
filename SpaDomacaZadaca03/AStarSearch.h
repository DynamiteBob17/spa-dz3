#pragma once

#include "GWeightedQueueSearch.h"

class AStarSearch : public GWeightedQueueSearch {
protected:
	void search() override;
	long sleepMin() override;
	long sleepMax() override;

public:
	AStarSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	std::string getIdentifier() override;
};
