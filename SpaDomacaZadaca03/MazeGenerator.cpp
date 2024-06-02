#include "MazeGenerator.h"

#include <stdexcept>
#include <random>
#include <vector>

static int removeRandomElement(std::vector<int>& vec) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(0, vec.size() - 1);

    int randomIndex = dis(gen);
    int element = vec[randomIndex];
    vec.erase(vec.begin() + randomIndex);

    return element;
}

void MazeGenerator::generate(int x, int y, float** maze) {
    maze[x][y] = .5f;

    if (maze[x - 2][y] != .5f || maze[x + 2][y] != .5f
        || maze[x][y - 2] != .5f || maze[x][y + 2] != .5f) {
        std::vector<int> directions = { 0, 1, 2, 3 };

        while (!directions.empty()) {
            int dir = removeRandomElement(directions);
            int nx = x, ny = y, mx = x, my = y;

            // after randomly picking a direction, get the wall set for removal between 2 tiles/cells
            // and the potentially unvisited passage tile that connects the wall with the current x, y
            if (dir == 0) {
                ny -= 2;
                my -= 1;
            } else if (dir == 1) {
                ny += 2;
                my += 1;
            } else if (dir == 2) {
                nx -= 2;
                mx -= 1;
            } else if (dir == 3) {
                nx += 2;
                mx += 1;
            }

            // carve the chosen path if we haven't visited the selected passage tile
            // by removing the wall and continuing the recursion on the selected tile
            if (maze[nx][ny] != .5f) {
                maze[mx][my] = .5f;
                generate(nx, ny, maze);
            }
        }
    }
}

float** MazeGenerator::generateMaze(int c, int r) {
    if (c % 2 == 0 || r % 2 == 0 || c < 3 || r < 3) {
        throw std::invalid_argument("Both columns and rows of the maze must be odd numbers and >= 3.");
    }

    int columns = c + 2, rows = r + 2;

    float** maze = new float* [columns];
    for (int i = 0; i < columns; ++i) {
        maze[i] = new float[rows];
    }

    // creates a grid which has a fake outer helper visited layer as 0.5,
    // then another layer of borders as walls,
    // then in that border of walls an alternating pattern of walls and passages,
    // like this:
    // .5 .5 .5 .5 .5 .5 .5
    // .5  1  1  1  1  1 .5
    // .5  1  0  1  0  1 .5
    // .5  1  1  0  1  1 .5
    // .5  1  0  1  0  1 .5
    // .5  1  1  1  1  1 .5
    // .5 .5 .5 .5 .5 .5 .5
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            maze[i][j] = 0.;

            if (i % 2 == 1 || j % 2 == 1)
                maze[i][j] = 1;
            if (i == 0 || j == 0 || i == columns - 1 || j == rows - 1)
                maze[i][j] = 0.5;
        }
    }

    // numbers like [2, 4, 6, ..., up to columns - 3];
    // these coordinates are guaranteed to be unvisited
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int>
        disX(1, ((columns - 2) / 2 + 1) - 1),
        disY(1, ((rows - 2) / 2 + 1) - 1);
    int startX = disX(gen) * 2;
    int startY = disY(gen) * 2;

    generate(startX, startY, maze);

    return maze;
}
