#pragma once

#include <iostream>

class Cell {
public:
    enum class Type {
        PASSAGE,
        WALL,
        ESCAPE
    };

    Cell();
    Cell(int row, int column, Type type);
    int getRow() const;
    int getColumn() const;
    bool isPassage() const;
    bool isWall() const;
    bool isEscape() const;
    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;

private:
    int row;
    int column;
    Type type;
};
