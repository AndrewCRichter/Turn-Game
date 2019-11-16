#include "World.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
std::vector<int> WorldGenHelper(std::vector<std::vector<int>> world, int height, int xStart, int xEnd, int zStart, int zEnd)
{
	if (xEnd + 1 > xStart)
	{
		world[xStart + (xEnd - xStart) / 2][zStart] = std::cmath.rand() % (2 * (std::abs(world[xStart][zStart] - world[xEnd][zStart]) + std::cmath.min(world[xStart][zStart] ,world[xEnd][zStart]));
		world[xStart + (xEnd - xStart) / 2][zEnd] = std::cmath.rand() % (2 * (std::abs(world[xStart][zEnd] - world[xEnd][zStart]) + std::cmath.min(world[xStart][zEnd] ,world[xEnd][zEnd]));
	}
	if (zEnd + 1 > zStart)
	{
		world[xStart][zStart + (zEnd - zStart) / 2] = std::cmath.rand() % (2 * (std::abs(world[xStart][zStart] - world[xStart][zEnd]) + std::cmath.min(world[xStart][zStart] ,world[xStart][zEnd]));
		world[xEnd][zStart + (zEnd - zStart) / 2] = std::cmath.rand() % (2 * (std::abs(world[xEnd][zStart] - world[xEnd][zEnd]) + std::cmath.min(world[xEnd][zStart] - world[xEnd][zEnd]));
	}
	if (xEnd + 1 > xStart && zEnd + 1 > zStart)
	{
		world[xStart + (xEnd - xStart) / 2][zStart + (zEnd - zStart) / 2] = (world[xStart][zStart] + world[xEnd][zEnd] + world[xStart][zEnd] + world[xEnd][zStart]) / 4;
	}
}

World::World(std::string fileName, int height, int width, int depth)
{
	bool good = true;
	std::ifstream inputWorld;
	inputWorld.open(fileName);
	int i, j, k;
	inputWorld >> i >> j >> k;
	if (inputWorld.good) {
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
					if (!inputWorld.good)
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
	std::vector<vector<int>> flatWorld;
	flatWorld.resize(depth);
	for (i = 0; i < depth; ++i)
	{
		flatWorld[i].resize(width);
	}
}
