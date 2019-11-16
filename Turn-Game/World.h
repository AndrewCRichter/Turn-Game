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
	World(std::vector<std::vector<std::vector<int>>> inputWorld, int height, int width, int depth)
	{
		world = inputWorld;
		this->height = height;
		this->width = width;
		this->depth = depth;
	}
	std::vector<std::vector<int>> getSlice(int x, int z, int xDirection, int zDirection)
	{
		std::vector<std::vector<int>> slice;
		int i = 0;
		for (; x >= 0 && x < width && z >= 0 && z < depth && world[x][z] != EMPTY; x -= xDirection, z -= zDirection);
		for (x += xDirection, z += zDirection; x >= 0 && x < width && y >= 0 && z < depth && world[x][z] != EMPTY; ++i)
		{
			slice.push_back(world[x][z]);
		}
		return slice;

	}
};

#endif // THING