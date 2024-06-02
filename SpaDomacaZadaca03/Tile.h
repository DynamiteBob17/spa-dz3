#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile {
	static const float BORDER_STROKE;
	static const sf::Color BORDER_COLOR;
	static const sf::Color START_COLOR;
	static const sf::Color GOAL_COLOR;
	static const sf::Color OPEN_COLOR;
	static const sf::Color SOLID_COLOR;
	static const sf::Color MARKED_COLOR;
	static const sf::Color CHECKED_COLOR;
	static const sf::Color PATH_COLOR;

	Tile* parent;
	int column, row;
	int gCost, hCost, fCost;
	bool start, goal;
	bool checked, path, marked;
	bool solid;
	sf::Color currentColor;

	void setColorBasedOnState();

public:
	Tile();
	~Tile();
	Tile(int column, int row);
	void draw(sf::RenderWindow& window, float tileWidth, float tileHeight, float offsetY);
	
	bool operator==(const Tile& other);
	bool operator!=(const Tile& other);
	friend std::ostream& operator<<(std::ostream& os, const Tile& obj);

	void setStart(bool start);
	void setGoal(bool goal);
	void setSolid(bool solid);
	void setChecked(bool checked);
	void setPath(bool path);
	void setMarked(bool marked);

	int getManhattanDistance(const Tile& other);

	Tile* getParent();
	void setParent(Tile* parent);
	bool hasParent();

	int getColumn();
	int getRow();
	int getGCost();
	int getHCost();
	int getFCost();
	void setGCost(int gCost);
	void setHCost(int hCost);
	void setFCost(int fCost);
	bool isStart();
	bool isGoal();
	bool notChecked();
	bool notSolid();
};
