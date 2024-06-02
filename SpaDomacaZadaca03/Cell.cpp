#include "Cell.h"

Cell::Cell() {
    row = 0;
    column = 0;
    type = Type::PASSAGE;
}

Cell::Cell(int row, int column, Type type) : row(row), column(column), type(type) {}

int Cell::getRow() const {
    return row;
}

int Cell::getColumn() const {
    return column;
}

bool Cell::isPassage() const {
    return type == Type::PASSAGE;
}

bool Cell::isWall() const {
    return type == Type::WALL;
}

bool Cell::isEscape() const {
    return type == Type::ESCAPE;
}

bool Cell::operator==(const Cell& other) const {
    return row == other.row && column == other.column && type == other.type;
}

bool Cell::operator!=(const Cell& other) const {
    return !(*this == other);
}
