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
	World(std::string fileName, int height, int width, int depth);
	std::vector<std::vector<int>> getSlice(int x, int z, int xDirection, int zDirection, int* offset);
};

#endif // THING