#pragma once

#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int size;

    void makeSet(int i);

public:
    DisjointSet(int size);
    int getSize() const;
    int find(int i);
    bool unionSets(int i, int j);
};
