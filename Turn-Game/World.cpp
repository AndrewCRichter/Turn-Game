#include "World.h"
#include <fstream>
#include <cmath>
#include <cstdlib>

int min(int a, int b) { return a < b ? a : b; }

int WorldGenVal(int x, int y)
{
	return std::rand() % (int)(1.25 * std::abs(x - y) + .5 ) + min(x, y);
}
void WorldGenHelper(std::vector<std::vector<int>> &world, int height, int xStart, int xEnd, int zStart, int zEnd)
{
	bool again = false;
    int xMid = xStart + (xEnd - xStart) / 2,
        zMid = zStart + (zEnd - zStart) / 2;
	if (xEnd + 1 > xStart)
	{
		world[xMid][zStart] = WorldGenVal(world[xStart][zStart], world[xEnd][zStart]);
		again = true;
	}
	if (zEnd + 1 > zStart)
	{
		world[xStart][zMid] = WorldGenVal(world[xStart][zStart], world[xStart][zEnd]);
		again = true;
	}
	if (xEnd + 1 > xStart && zEnd + 1 > zStart)
	{
		world[xMid][zMid] = WorldGenVal(world[xStart][zStart], world[xEnd][zEnd]);
		again = true;
	}
	if (again)
	{
		WorldGenHelper(world, height, xStart, xMid, zStart, zMid);
		WorldGenHelper(world, height, xStart, xMid, zStart, zMid);
		WorldGenHelper(world, height, xStart, xMid, zStart, zMid);
		WorldGenHelper(world, height, xStart, xMid, zStart, zMid);
	}
}

World::World(std::string fileName, Tileset ts, int height, int width, int depth)
{
    this->tiles = ts;
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

World::World(std::vector<std::vector<std::vector<int>>> world, Tileset ts, int height, int width, int depth)
{
    this->world = world;
    this->tiles = ts;
    this->height = height;
    this->width = width;
    this->depth = depth;
}


std::vector<std::vector<int>> World::getSlice(int x, int z, Direction dir, int* offset)
{
    int xDirection = DIRECTION_VALUES[dir][0],
        zDirection = DIRECTION_VALUES[dir][1];
    std::vector<std::vector<int>> slice;
	int i = 0;
	*offset = -1;
    for (; x >= 0 && x < width && z >= 0 && z < depth && world[x][z][0] != EMPTY; x -= xDirection, z -= zDirection) {
        ++*offset;
    }
	for (x += xDirection, z += zDirection; x >= 0 && x < width && z >= 0 && z < depth && world[x][z][0] != EMPTY; x += xDirection, z += zDirection)
	{
		slice.push_back(world[x][z]);
	}
	return slice;

}
Tileset World::getTileset()
{
    return tiles;
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
