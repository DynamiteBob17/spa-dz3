#include "Grid.h"
#include "Canvas.h"
#include <stdexcept>

const int Grid::MAX_COLUMNS = Grid::calculateColumns(MAX_STEPS);
const int Grid::MAX_ROWS = Grid::calculateRows(MAX_STEPS);

Grid::Grid(int steps, float offsetY) : defaultSteps(steps), steps(steps), offsetY(offsetY), columns(calculateColumns(steps)), rows(calculateRows(steps)) {
    if (steps < 0) {
        throw std::invalid_argument("Steps cannot be negative.");
    }

    tiles = new Tile* [MAX_COLUMNS];
    for (int i = 0; i < MAX_COLUMNS; ++i) {
        tiles[i] = new Tile[MAX_ROWS];
        for (int j = 0; j < MAX_ROWS; ++j) {
            tiles[i][j] = Tile(i, j);
        }
    }

    startTile = &tiles[getDefaultStartX()][getDefaultStartY()];
    goalTile = &tiles[getDefaultGoalX()][getDefaultGoalY()];
    startTile->setStart(true);
    goalTile->setGoal(true);
    
    setTileSizes(Canvas::INITIAL_WIDTH, Canvas::INITIAL_HEIGHT);
}

void Grid::draw(sf::RenderWindow& window) {
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            tiles[i][j].draw(window, tileWidth, tileHeight, offsetY);
        }
    }
}

void Grid::setTileSizes(int canvasWidth, int canvasHeight) {
    tileWidth = (float)(canvasWidth) / columns;
    tileHeight = (float)(canvasHeight - offsetY) / rows;
}

void Grid::clear(bool clearPath, bool clearSolid, bool resetStartGoal) {
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (clearSolid) {
                tiles[i][j].setSolid(false);
            }
            if (clearPath) {
                tiles[i][j].setPath(false);
                tiles[i][j].setChecked(false);
                tiles[i][j].setMarked(false);
                tiles[i][j].setParent(nullptr);
            }
        }
    }

    if (resetStartGoal) {
        unsetStartGoal();
        setStartGoal(getDefaultStartX(), getDefaultStartY(), getDefaultGoalX(), getDefaultGoalY());
    }
}

void Grid::clearPath() {
    clear(true, false, false);
}

void Grid::clearSolid() {
    clear(false, true, false);
}

void Grid::clearAll() {
    clear(true, true, false);
}

void Grid::reset(int canvasWidth, int canvasHeight) {
    steps = defaultSteps;
    columns = calculateColumns(steps);
    rows = calculateRows(steps);
    setTileSizes(canvasWidth, canvasHeight);

    clear(true, true, true);
}

void Grid::randomMaze(MazeAlgo mazeAlgo) {
    unsetStartGoal();

    if (mazeAlgo == MazeAlgo::KRUSKAL) {
        Maze maze(rows, columns);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                // indices are flipped here because
                // the Maze class is created to be accessed as a matrix where
                // the i is row and j is column,
                // whereas the in the Grid and Tile classes i is column and j is row
                // to sort of match how things are drawn on the screen regarding the x and y coordinates
                tiles[j][i].setSolid(maze.getGrid()[i][j].isWall());
            }
        }
    }
    else if (mazeAlgo == MazeAlgo::REC_BACK) {
        auto maze = MazeGenerator::generateMaze(columns, rows);

        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < rows; ++j) {
                tiles[i][j].setSolid(maze[i + 1][j + 1] == 1);
            }
        }
    }

    int secondColumn = 1, firstRow = 0;
    int secondToLastColumn = columns - 2, lastRow = rows - 1;
    setStartGoal(secondColumn, firstRow, secondToLastColumn, lastRow);
}

// if this method is used, the setStartGoal method has to be used at an appropriate point afterward
void Grid::unsetStartGoal() {
    startTile->setStart(false);
    goalTile->setGoal(false);
}

void Grid::setStartGoal(int startColumn, int startRow, int goalColumn, int goalRow) {
    Tile* newStartTile = &tiles[startColumn][startRow];
    Tile* newGoalTile = &tiles[goalColumn][goalRow];
    newStartTile->setStart(true);
    newGoalTile->setGoal(true);
    startTile = newStartTile;
    goalTile = newGoalTile;

    // we don't do this automatically when changing start/goal tile on the canvas in the ui
    // to not change the colors already on the cells we are dragging over,
    // only when we drop the start/tile do we set that tile to non-solid, but we do that
    // in the mouse listener manually
    startTile->setSolid(false);
    goalTile->setSolid(false);
}

// this method marks the edges that are not checked,
// so it should be used before drawing the canvas/grid
std::vector<Tile*> Grid::getUncheckedEdges(Tile* tile) {
    std::vector<Tile*> edges;
    Tile* edge;
    int column, row;

    if ((column = tile->getColumn() - 1) >= 0) {
        edge = &tiles[column][tile->getRow()];
        if (edge->notSolid() && edge->notChecked()) {
            edges.push_back(edge);
            edge->setMarked(true);
        }
    }
    if ((row = tile->getRow() + 1) < rows) {
        edge = &tiles[tile->getColumn()][row];
        if (edge->notSolid() && edge->notChecked()) {
            edges.push_back(edge);
            edge->setMarked(true);
        }
    }
    if ((column = tile->getColumn() + 1) < columns) {
        edge = &tiles[column][tile->getRow()];
        if (edge->notSolid() && edge->notChecked()) {
            edges.push_back(edge);
            edge->setMarked(true);
        }
    }
    if ((row = tile->getRow() - 1) >= 0) {
        edge = &tiles[tile->getColumn()][row];
        if (edge->notSolid() && edge->notChecked()) {
            edges.push_back(edge);
            edge->setMarked(true);
        }
    }

    return edges;
}

void Grid::changeStep(GridDimensionChange gdc, int canvasWidth, int canvasHeight) {
    int steps = this->steps + (gdc == GridDimensionChange::DECREMENT ? -1 : 1);

    if (steps < 0 || steps > MAX_STEPS)
        return;

    this->steps = steps;
    this->columns = calculateColumns(steps);
    this->rows = calculateRows(steps);

    if (startTile->getColumn() >= columns || startTile->getRow() >= rows ||
        goalTile->getColumn() >= columns || goalTile->getRow() >= rows) {
        unsetStartGoal();
        setStartGoal(getDefaultStartX(), getDefaultStartY(), getDefaultGoalX(), getDefaultGoalY());
    }

    setTileSizes(canvasWidth, canvasHeight);
}

void Grid::decrement(int canvasWidth, int canvasHeight) {
    changeStep(GridDimensionChange::DECREMENT, canvasWidth, canvasHeight);
}

void Grid::increment(int canvasWidth, int canvasHeight) {
    changeStep(GridDimensionChange::INCREMENT, canvasWidth, canvasHeight);
}

void Grid::resetTileCosts() {
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            tiles[i][j].setGCost(0);
            tiles[i][j].setHCost(0);
            tiles[i][j].setFCost(0);
        }
    }
}

void Grid::calculateHCosts() {
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            tiles[i][j].setHCost(tiles[i][j].getManhattanDistance(*goalTile));
        }
    }
}

int Grid::calculateMaxHCost() {
    int furthestColumn = goalTile->getColumn() >= columns / 2 ? 0 : columns - 1;
    int furthestRow = goalTile->getRow() >= rows / 2 ? 0 : rows - 1;

    return goalTile->getManhattanDistance(tiles[furthestColumn][furthestRow]);
}

void Grid::uiSetStartTile(Tile* tile) {
    if (tile->isGoal()) return;

    startTile->setStart(false);
    tile->setStart(true);
    startTile = tile;
}

void Grid::uiSetGoalTile(Tile* tile) {
    if (tile->isStart()) return;

    goalTile->setGoal(false);
    tile->setGoal(true);
    goalTile = tile;
}

int Grid::calculateDimension(int min, int aspect, int steps) {
    return min + aspect * steps;
}

int Grid::calculateColumns(int steps) {
    return calculateDimension(MIN_COLUMNS, COLUMN_ASPECT, steps);
}

int Grid::calculateRows(int steps) {
    return calculateDimension(MIN_ROWS, ROW_ASPECT, steps);
}

int Grid::getDefaultStartX() const {
    return getColumns() / 4;
}

int Grid::getDefaultStartY() const {
    return getRows() / 2;
}

int Grid::getDefaultGoalX() const {
    return getColumns() * 3 / 4;
}

int Grid::getDefaultGoalY() const {
    return getRows() / 2;
}

int Grid::getSteps() const {
    return steps;
}

int Grid::getColumns() const {
    return columns;
}

int Grid::getRows() const {
    return rows;
}

float Grid::getYOffset() {
    return offsetY;
}

Tile* Grid::getTile(int column, int row) {
    return &tiles[column][row];
}

Tile* Grid::getStartTile() {
    return startTile;
}

Tile* Grid::getGoalTile() {
    return goalTile;
}
