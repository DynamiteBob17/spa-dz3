#include "Maze.h"

Maze::Maze(int height, int width) : height(height), width(width) {
    if (height < 3 || width < 3) {
        throw std::invalid_argument("Both the height and the width of the maze must be at least 3");
    }
    entranceColumn = 1;
    exitColumn = width - 3 + width % 2;
    grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
    fillGrid();
}

Maze::Maze(int size) : Maze(size, size) {}

void Maze::fillGrid() {
    fillAlternately();
    fillGaps();
    makeEntranceAndExit();
    generatePassages();
}

void Maze::putCell(int row, int column, Cell::Type type) {
    grid[row][column] = Cell(row, column, type);
}

void Maze::fillAlternately() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if ((i & 1) == 0 || (j & 1) == 0) {
                putCell(i, j, Cell::Type::WALL);
            }
            else {
                putCell(i, j, Cell::Type::PASSAGE);
            }
        }
    }
}

void Maze::fillGaps() {
    if (height % 2 == 0) wallLastRow();
    if (width % 2 == 0) wallLastColumn();
}

void Maze::wallLastColumn() {
    for (int i = 0; i < height; ++i) {
        putCell(i, width - 1, Cell::Type::WALL);
    }
}

void Maze::wallLastRow() {
    for (int i = 0; i < width; ++i) {
        putCell(height - 1, i, Cell::Type::WALL);
    }
}

int Maze::getEntranceColumn() const {
    return entranceColumn;
}

int Maze::getExitColumn() const {
    return exitColumn;
}

void Maze::makeEntranceAndExit() {
    putCell(0, getEntranceColumn(), Cell::Type::PASSAGE);
    putCell(height - 1, getExitColumn(), Cell::Type::PASSAGE);
    if (height % 2 == 0) {
        putCell(height - 2, getExitColumn(), Cell::Type::PASSAGE);
    }
}

void Maze::generatePassages() {
    PassageTree passageTree(height, width);
    auto passages = passageTree.generate();
    for (const auto& cell : passages) {
        grid[cell.getRow()][cell.getColumn()] = cell;
    }
}

std::function<void(Cell)> Maze::putCell() {
    return [this](Cell cell) {
        grid[cell.getRow()][cell.getColumn()] = cell;
        };
}

Cell Maze::getEntrance() const {
    return grid[0][getEntranceColumn()];
}

Cell Maze::getExit() const {
    return grid[height - 1][getExitColumn()];
}

Cell::Type Maze::intToType(int val) {
    return val == 1 ? Cell::Type::WALL : Cell::Type::PASSAGE;
}

int Maze::typeToInt(const Cell& cell) const {
    return cell.isWall() ? 1 : 0;
}

std::vector<std::vector<Cell>> Maze::getGrid() const {
    return grid;
}
