#pragma once

#include "Grid.h"
#include "Canvas.h"

class MouseListener {
private:
	Grid& grid;
	Canvas& canvas;
	sf::RenderWindow& window;
	bool startPressed, goalPressed;
	bool enabled;

	int mapMouseXToColumn(const sf::Event::MouseMoveEvent& event);
	int mapMouseYToRow(const sf::Event::MouseMoveEvent& event);
	Tile* getTileFromMouse(const sf::Event::MouseMoveEvent& event, bool isStartOrGoal);
	int mapMouseXToColumn(const sf::Event::MouseButtonEvent& event);
	int mapMouseYToRow(const sf::Event::MouseButtonEvent& event);
	Tile* getTileFromMouse(const sf::Event::MouseButtonEvent& event, bool isStartOrGoal);
	void setTileState(const sf::Event::MouseButtonEvent& event, bool calledOnMousePressed);
	void setTileState(const sf::Event::MouseMoveEvent& event);

public:
	MouseListener(Grid& grid, Canvas& canvas, sf::RenderWindow& window);

	void handleEvent(const sf::Event& event);
	void enable();
	void disable();
};
