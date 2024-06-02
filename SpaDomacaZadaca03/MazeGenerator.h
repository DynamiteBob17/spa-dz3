#pragma once

class MazeGenerator {
private:
	static void generate(int x, int y, float** maze);

public:
	static float** generateMaze(int c, int r);
};
