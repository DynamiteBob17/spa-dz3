#include "Tile.h"

#include "cmath"

const float Tile::BORDER_STROKE = 1.f;
const sf::Color Tile::BORDER_COLOR = sf::Color(64, 64, 64);
const sf::Color Tile::START_COLOR = sf::Color(221, 91, 91);
const sf::Color Tile::GOAL_COLOR = sf::Color(119, 221, 119);
const sf::Color Tile::OPEN_COLOR = sf::Color(249, 248, 231);
const sf::Color Tile::SOLID_COLOR = sf::Color(0, 51, 102);
const sf::Color Tile::MARKED_COLOR = sf::Color(30, 119, 168);
const sf::Color Tile::CHECKED_COLOR = sf::Color(86, 163, 240);
const sf::Color Tile::PATH_COLOR = sf::Color(255, 165, 0);

void Tile::setColorBasedOnState() {
	if (solid)
		currentColor = SOLID_COLOR;
	else if (path)
		currentColor = PATH_COLOR;
	else if (checked)
		currentColor = CHECKED_COLOR;
	else if (marked)
		currentColor = MARKED_COLOR;
	else
		currentColor = OPEN_COLOR;
}

Tile* parent;
int column, row;
int gCost, hCost, fCost;
bool start, goal;
bool checked, path, marked;
bool solid;
sf::Color currentColor;

Tile::Tile() {
	column = 0;
	row = 0;
	parent = nullptr;
	gCost = hCost = fCost = 0;
	start = goal = false;
	checked = path = marked = false;
	solid = false;
	currentColor = OPEN_COLOR;
}

Tile::~Tile() {
	delete parent;
}

Tile::Tile(int column, int row) : column(column), row(row) {
	parent = nullptr;
	gCost = hCost = fCost = 0;
	start = goal = false;
	checked = path = marked = false;
	solid = false;
	currentColor = OPEN_COLOR;
}

void Tile::draw(sf::RenderWindow& window, float tileWidth, float tileHeight, float offsetY) {
	float x = tileWidth * column;
	float y = tileHeight * row + offsetY;

	sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
	tile.setPosition(x, y);
	tile.setFillColor(currentColor);
	tile.setOutlineColor(BORDER_COLOR);
	tile.setOutlineThickness(BORDER_STROKE);

	window.draw(tile);
}

bool Tile::operator==(const Tile& other) {
	return this->column == other.column && this->row == other.row;
}

bool Tile::operator!=(const Tile& other) {
	return !(*this == other);
}

void Tile::setStart(bool start) {
	if (start && goal) return;

	this->start = start;

	if (start) {
		currentColor = START_COLOR;
	}
	else {
		setColorBasedOnState();
	}
}

void Tile::setGoal(bool goal) {
	if (goal && start) return;

	this->goal = goal;

	if (goal) {
		currentColor = GOAL_COLOR;
	}
	else {
		setColorBasedOnState();
	}
}

void Tile::setSolid(bool solid) {
	if (solid && (start || goal)) return;

	this->solid = solid;

	if (!start && !goal) {
		setColorBasedOnState();
	}
}

void Tile::setChecked(bool checked) {
	this->checked = checked;

	if (!start && !goal) {
		setColorBasedOnState();
	}
}

void Tile::setPath(bool path) {
	this->path = path;

	if (!start && !goal) {
		setColorBasedOnState();
	}
}

void Tile::setMarked(bool marked) {
	this->marked = marked;

	if (!start && !goal) {
		setColorBasedOnState();
	}
}

int Tile::getManhattanDistance(const Tile& other) {
	return std::abs(this->column - other.column) +
		std::abs(this->row - other.row);
}

Tile* Tile::getParent() {
	return parent;
}

void Tile::setParent(Tile* parent) {
	this->parent = parent;
}

bool Tile::hasParent() {
	return parent != nullptr;
}

int Tile::getColumn() {
	return column;
}

int Tile::getRow() {
	return row;
}

int Tile::getGCost() {
	return gCost;
}

int Tile::getHCost() {
	return hCost;
}

int Tile::getFCost() {
	return fCost;
}

void Tile::setGCost(int gCost) {
	this->gCost = gCost;
}

void Tile::setHCost(int hCost) {
	this->hCost = hCost;
}

void Tile::setFCost(int fCost) {
	this->fCost = fCost;
}

bool Tile::isStart() {
	return start;
}

bool Tile::isGoal() {
	return goal;
}

bool Tile::notChecked() {
	return !checked;
}

bool Tile::notSolid() {
	return !solid;
}

std::ostream& operator<<(std::ostream& os, const Tile& obj) {
	os << "(" << column << ", " << row << ")" << "=";

	if (start) os << "START";
	else if (goal) os << "GOAL";
	else if (solid) os << "SOLID";
	else os << "OPEN";

	return os;
}
