#pragma once
#ifndef THING
#define THING

#include <vector>

class World
{
private:
	const int EMPTY = -1;
	int height;
	int width;
	int depth;
	std::vector<std::vector<std::vector<int>>> world;
public:
	World(std::vector<std::vector<std::vector<int>>> inputWorld, int height, int width, int depth);
	std::vector<std::vector<int>> getSlice(int x, int z, int xDirection, int zDirection);
};

#endif // THING