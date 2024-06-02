#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "MazeAlgo.h"
#include "GridDimensionChange.h"
#include "Maze.h"
#include "MazeGenerator.h"

class Grid {
private:
    int steps;
    const int defaultSteps;
    int columns, rows;
    Tile** tiles;
    Tile* startTile;
    Tile* goalTile;
    float tileWidth, tileHeight;
    float offsetY;

    void unsetStartGoal();
    void setStartGoal(int startColumn, int startRow, int goalColumn, int goalRow);
    void changeStep(GridDimensionChange gdc, int canvasWidth, int canvasHeight);
    static int calculateDimension(int min, int aspect, int steps);
    static int calculateColumns(int steps);
    static int calculateRows(int steps);
    int getDefaultStartX() const;
    int getDefaultStartY() const;
    int getDefaultGoalX() const;
    int getDefaultGoalY() const;

public:
    // these are just for painting the canvas so that
    // every time we change the number of columns and rows
    // we add 6 columns and 4 rows to keep some kind of
    // aspect ratio so that the tiles appear as close as possible to
    // a square; also, we are not making it 3 and 2 because we need the
    // number of columns and rows to always be odd
    static const int COLUMN_ASPECT = 6;
    static const int ROW_ASPECT = 4;
    static const int MAX_STEPS = 15;
    static const int MIN_COLUMNS = 5;
    static const int MAX_COLUMNS;
    static const int MIN_ROWS = 3;
    static const int MAX_ROWS;

    Grid(int steps, float offsetY);

    void draw(sf::RenderWindow& window);
    void setTileSizes(int canvasWidth, int canvasHeight);
    void clear(bool clearPath, bool clearSolid, bool resetStartGoal);
    void clearPath();
    void clearSolid();
    void clearAll();
    void reset(int canvasWidth, int canvasHeight);
    void randomMaze(MazeAlgo mazeAlgo);
    std::vector<Tile*> getUncheckedEdges(Tile* tile);
    void decrement(int canvasWidth, int canvasHeight);
    void increment(int canvasWidth, int canvasHeight);
    void resetTileCosts();
    void calculateHCosts();
    int calculateMaxHCost();
    void uiSetStartTile(Tile* tile);
    void uiSetGoalTile(Tile* tile);

    int getSteps() const;
    int getColumns() const;
    int getRows() const;
    float getYOffset();
    Tile* getTile(int column, int row);
    Tile* getStartTile();
    Tile* getGoalTile();
};
