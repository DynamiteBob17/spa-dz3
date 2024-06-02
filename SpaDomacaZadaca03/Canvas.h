#pragma once

#include "Grid.h"

class Canvas {
private:
	sf::RenderWindow& window;
	Grid& grid;
	bool searchRunning;
	bool pauseRunningSearch;
	bool stopRunningSearch;

public:
	static const int INITIAL_WIDTH;
	static const int INITIAL_HEIGHT;

	Canvas(sf::RenderWindow& window, Grid& grid);
	void draw();

	bool searchNotRunning();
	bool isPauseRunningSearch();
	bool isStopRunningSearch();
	void setSearchRunning(bool searchRunning);
	void togglePauseRunningSearch();
	void turnOffPauseRunningSearch();
	void setStopRunningSearch(bool stopRunningSearch);
};
