#pragma once

#include "SimpleStackSearch.h"

class DepthFirstSearch : public SimpleStackSearch {
protected:
	void search() override;
	long sleepMin() override;
	long sleepMax() override;

public:
	DepthFirstSearch(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	std::string getIdentifier() override;
};
