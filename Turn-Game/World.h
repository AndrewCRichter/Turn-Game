#pragma once
#ifndef THING
#define THING

#include <vector>
#include <string>

class World
{
private:
	const int EMPTY = -1;
	int height;
	int width;
	int depth;
	std::vector<std::vector<std::vector<int>>> world;
public:
	int WorldGenVal(int x, int y);
	void WorldGenHelper(std::vector<std::vector<int>> &world, int xStart, int xEnd, int zStart, int zEnd);
	World(std::string fileName, int height, int width, int depth);
	std::vector<std::vector<int>> getSlice(int x, int z, int xDirection, int zDirection, int* offset);
	void WorldGen(std::string fileName, int height, int width, int depth, int cut);
};

#endif // THING