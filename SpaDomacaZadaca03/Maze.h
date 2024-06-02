#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include "Cell.h"
#include "PassageTree.h"

class Maze {
private:
    int height;
    int width;
    std::vector<std::vector<Cell>> grid;
    int entranceColumn;
    int exitColumn;
    bool isSolved = false;

    void fillGrid();
    void putCell(int row, int column, Cell::Type type);
    void fillAlternately();
    void fillGaps();
    void wallLastColumn();
    void wallLastRow();
    void makeEntranceAndExit();
    void generatePassages();
    std::function<void(Cell)> putCell();
    Cell getEntrance() const;
    Cell getExit() const;
    static Cell::Type intToType(int val);
    int typeToInt(const Cell& cell) const;

public:
    Maze(int height, int width);
    Maze(int size);
    std::vector<std::vector<Cell>> getGrid() const;
    int getEntranceColumn() const;
    int getExitColumn() const;
};
