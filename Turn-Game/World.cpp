#include "World.h"

World::World(std::vector<std::vector<std::vector<int>>> inputWorld, int height, int width, int depth)
{
	world = inputWorld;
	this->height = height;
	this->width = width;
	this->depth = depth;
}

std::vector<std::vector<int>> World::getSlice(int x, int z, int xDirection, int zDirection)
{
	std::vector<std::vector<int>> slice;
	int i = 0;
	for (; x >= 0 && x < width && z >= 0 && z < depth && world[x][z][0] != EMPTY; x -= xDirection, z -= zDirection);
	for (x += xDirection, z += zDirection; x >= 0 && x < width && z >= 0 && z < depth && world[x][z][0] != EMPTY; ++i)
	{
		slice.push_back(world[x][z]);
	}
	return slice;

}