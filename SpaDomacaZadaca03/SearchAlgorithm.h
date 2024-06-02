#pragma once

#include "Grid.h"
#include "Canvas.h"
#include "SoundPlayer.h"

class SearchAlgorithm {
protected:
	Grid& grid;
	Canvas& canvas;
	SoundPlayer& soundPlayer;
	Tile* startTile;
	Tile* goalTile;
	long sleepMs;

	virtual void search() = 0;
	virtual long sleepMin() = 0;
	virtual long sleepMax() = 0;
	
	bool commonMiddleStep(Tile* current);
	void trackAndFillPath();
	void sleep();
	void precalculateSleep();

public:
	SearchAlgorithm(Grid& grid, Canvas& canvas, SoundPlayer& soundPlayer);
	void run();
	virtual std::string getIdentifier() = 0;
};
