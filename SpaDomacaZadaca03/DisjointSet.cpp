#include "DisjointSet.h"

DisjointSet::DisjointSet(int size) : size(size), parent(size), rank(size) {
    for (int i = 0; i < size; ++i) {
        makeSet(i);
    }
}

void DisjointSet::makeSet(int i) {
    parent[i] = i;
    rank[i] = 0;
}

int DisjointSet::getSize() const {
    return size;
}

int DisjointSet::find(int i) {
    if (i != parent[i]) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

bool DisjointSet::unionSets(int i, int j) {
    int iRoot = find(i);
    int jRoot = find(j);
    if (iRoot == jRoot) {
        return false;
    }
    if (rank[iRoot] < rank[jRoot]) {
        parent[iRoot] = jRoot;
    }
    else {
        parent[jRoot] = iRoot;
        if (rank[iRoot] == rank[jRoot]) {
            rank[iRoot]++;
        }
    }
    size--;
    return true;
}
