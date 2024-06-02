#include "PassageTree.h"

PassageTree::PassageTree(int height, int width)
    : height((height - 1) / 2), width((width - 1) / 2) {}

std::vector<PassageTree::Edge> PassageTree::createEdges() const {
    std::vector<Edge> edges;
    for (int column = 1; column < width; ++column) {
        edges.emplace_back(toIndex(0, column), toIndex(0, column - 1));
    }
    for (int row = 1; row < height; ++row) {
        edges.emplace_back(toIndex(row, 0), toIndex(row - 1, 0));
    }
    for (int row = 1; row < height; ++row) {
        for (int column = 1; column < width; ++column) {
            edges.emplace_back(toIndex(row, column), toIndex(row, column - 1));
            edges.emplace_back(toIndex(row, column), toIndex(row - 1, column));
        }
    }
    return edges;
}

int PassageTree::toIndex(int row, int column) const {
    return row * width + column;
}

Cell PassageTree::fromIndex(int index) const {
    int row = index / width;
    int column = index % width;
    return Cell(row, column, Cell::Type::PASSAGE);
}

bool PassageTree::connects(const Edge& edge, DisjointSet& disjointSet) const {
    return disjointSet.unionSets(edge.firstCell, edge.secondCell);
}

std::vector<PassageTree::Edge> PassageTree::buildRandomSpanningTree(std::vector<Edge>& edges) const {
    DisjointSet disjointSets(width * height);
    std::vector<Edge> tree;
    for (const auto& edge : edges) {
        if (connects(edge, disjointSets)) {
            tree.push_back(edge);
        }
    }
    return tree;
}

Cell PassageTree::getPassage(const Cell& first, const Cell& second) const {
    int row = first.getRow() + second.getRow() + 1;
    int column = first.getColumn() + second.getColumn() + 1;
    return Cell(row, column, Cell::Type::PASSAGE);
}

std::vector<Cell> PassageTree::createPassages(const std::vector<Edge>& spanningTree) const {
    std::vector<Cell> passages;
    for (const auto& edge : spanningTree) {
        Cell first = fromIndex(edge.firstCell);
        Cell second = fromIndex(edge.secondCell);
        passages.push_back(getPassage(first, second));
    }
    return passages;
}

std::vector<Cell> PassageTree::generate() {
    std::vector<Edge> edges = createEdges();
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(edges.begin(), edges.end(), gen);
    std::vector<Edge> tree = buildRandomSpanningTree(edges);
    return createPassages(tree);
}
