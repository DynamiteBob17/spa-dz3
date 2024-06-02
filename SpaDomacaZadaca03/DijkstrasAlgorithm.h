#pragma once

#include "GWeightedQueueSearch.h"

class DijkstrasAlgorithm : public GWeightedQueueSearch {
protected:
	void search() override;
	long sleepMin() override;
	long sleepMax() override;

public:
	DijkstrasAlgorithm(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	std::string getIdentifier() override;
};
