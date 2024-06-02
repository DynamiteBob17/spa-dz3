#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include "Cell.h"
#include "DisjointSet.h"

class PassageTree {
private:
    struct Edge {
        int firstCell;
        int secondCell;
        Edge(int first, int second) : firstCell(first), secondCell(second) {}
    };

    int height;
    int width;

    int toIndex(int row, int column) const;
    Cell fromIndex(int index) const;
    Cell getPassage(const Cell& first, const Cell& second) const;
    std::vector<Edge> createEdges() const;
    std::vector<Edge> buildRandomSpanningTree(std::vector<Edge>& edges) const;
    bool connects(const Edge& edge, DisjointSet& disjointSet) const;
    std::vector<Cell> createPassages(const std::vector<Edge>& spanningTree) const;

public:
    PassageTree(int height, int width);
    std::vector<Cell> generate();
};
