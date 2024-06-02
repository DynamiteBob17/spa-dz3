#pragma once

#include "SimpleQueueSearch.h"

class GreedyBestFirstSearch : public SimpleQueueSearch {
protected:
	void search() override;
	long sleepMin() override;
	long sleepMax() override;

public:
	GreedyBestFirstSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	std::string getIdentifier() override;
};
