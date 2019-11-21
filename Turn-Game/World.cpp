#include "World.h"
#include <fstream>
#include <cmath>
#include <cstdlib>

int min(int a, int b) { return a < b ? a : b; }

std::vector<int> WorldGenHelper(std::vector<std::vector<int>> world, int height, int xStart, int xEnd, int zStart, int zEnd)
{
	if (xEnd + 1 > xStart)
	{
		int diff1 = std::abs(world[xStart][zStart] - world[xEnd][zStart]),
			diff2 = std::abs(world[xStart][zEnd]   - world[xEnd][zEnd]); /*Assuming that this should this be zEnd for the second one istead of zStart*/
		int min1 = min(world[xStart][zStart], world[xEnd][zStart]),
			min2 = min(world[xStart][zEnd],   world[xEnd][zEnd]);
		world[xStart + (xEnd - xStart) / 2][zStart] = std::rand() % (2 * diff1) + min1;
		world[xStart + (xEnd - xStart) / 2][zEnd]   = std::rand() % (2 * diff2) + min2;
	}
	if (zEnd + 1 > zStart)
	{
		int diff1 = std::abs(world[xStart][zStart] - world[xStart][zEnd]),
			diff2 = std::abs(world[xEnd][zStart]   - world[xEnd][zEnd]);
		int min1 = min(world[xStart][zStart], world[xStart][zEnd]),
			min2 = min(world[xEnd][zStart],   world[xEnd][zEnd]);
		world[xStart + (xEnd - xStart) / 2][zStart] = std::rand() % (2 * diff1) + min1;
		world[xStart + (xEnd - xStart) / 2][zEnd] = std::rand() % (2 * diff2) + min2;
	}
	if (xEnd + 1 > xStart && zEnd + 1 > zStart)
	{
		world[xStart + (xEnd - xStart) / 2][zStart + (zEnd - zStart) / 2] = (world[xStart][zStart]
																		   + world[xEnd][zEnd]
																		   + world[xStart][zEnd]
																		   + world[xEnd][zStart]) / 4;
	}
}

World::World(std::string fileName, int height, int width, int depth)
{
	bool good = true;
	std::ifstream inputWorld;
	inputWorld.open(fileName);
	int i, j, k;
	inputWorld >> i >> j >> k;
	if (inputWorld.good()) {
		world.resize(depth);
		for (i = 0; i < depth && good; ++i)
		{
			world[i].resize(width);
			for (j = 0; j < width && good; ++j)
			{
				world.resize(height);
				for (k = 0; k < height && good; ++k)
				{
					int next;
					inputWorld >> next;
					if (!inputWorld.good())
					{
						good = false;
					}
					else
					{
						
						world[i][j][k] = next;
					}
				}
			}
		}
		this->height = height;
		this->width = width;
		this->depth = depth;
	}
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
void WorldGen(std::string fileName, int height, int width, int depth)
{
	std::vector<std::vector<int>> flatWorld;
	flatWorld.resize(depth);
	int i;
	for (i = 0; i < depth; ++i)
	{
		flatWorld[i].resize(width);
	}
}
