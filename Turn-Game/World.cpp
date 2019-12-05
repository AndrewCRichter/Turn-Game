#include "World.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int World::WorldGenVal(int x, int y)
{
	return std::rand() % (1.5 * (x < y ? y - x : x - y)) + x < y ? x : y;
}
void World::WorldGenHelper(std::vector<std::vector<int>> &world, int xStart, int xEnd, int zStart, int zEnd)
{
	bool again = false;
	int xMid = xStart + (xEnd - xStart) / 2,
		zMid = zStart + (zEnd - zStart) / 2;
	if (xEnd + 1 > xStart)
	{
		world[xMid][zEnd] = WorldGenVal(world[xStart][zEnd], world[xEnd][zEnd]);
		if (zStart == 0)
		{
			world[xMid][zStart] = WorldGenVal(world[xStart][zStart], world[xEnd][zStart]);
		}
		again = true;
	}
	if (zEnd + 1 > zStart)
	{
		world[xEnd][zMid] = WorldGenVal(world[xEnd][zStart], world[xEnd][zEnd]);
		if (xStart == 0)
		{
			world[xStart][zMid] = WorldGenVal(world[xStart][zStart], world[xStart][zEnd]);
		}
		again = true;
	}
	if (xEnd + 1 > xStart && zEnd + 1 > zStart)
	{
		world[xMid][zMid] = WorldGenVal(world[xStart][zStart], world[xEnd][zEnd]);
		again = true;
	}
	if (again)
	{
		//The order matters of these lines. This order is correct.
		WorldGenHelper(world, xStart, xMid, zStart, zMid);
		WorldGenHelper(world, xMid, xEnd, zStart, zMid);
		WorldGenHelper(world, xStart, xMid, zMid, zEnd);
		WorldGenHelper(world, xMid, xEnd, zMid, zEnd);
	}
}

World::World(std::string fileName, Tileset ts, int height, int width, int depth)
{
	const std::string SEP = "\n",
				COMMA = ",";
	int height,
		width,
		depth,
		next;
	bool iRow,
		jRow,
		kRow;
    this->tiles = ts;
	bool good = true;
	std::string ascii;
	std::ifstream inputWorld;
	inputWorld.open(fileName);
	int i, j, k;
	inputWorld >> height >> ascii >> width >> ascii >> depth >> ascii;
	if (inputWorld.good()) {
		world.resize(depth);
		for (i = 0; i < depth && good; ++i)
		{
			world[i].resize(width);
			jRow = true;
			for (j = 0; j < width && good; ++j)
			{
				kRow = true;
				world.resize(height);
				for (k = 0; kRow && good; ++k)
				{
					inputWorld >> next >> ascii;
					if (!inputWorld.good())
					{
						good = false;
					}
					else
					{
						world[i][j][k] = next;
						if (ascii != COMMA && ascii == SEP)
						{
							kRow = false;
						}
						else if (ascii == SEP + SEP)
						{
							jRow = false;
							kRow = false;
						}
						else
						{
							iRow = false;
							jRow = false;
							kRow = false;
						}
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
void World::WorldGen(std::string fileName, int height, int width, int depth,int cut)
{
	const char COMMA = ',';
	std::ofstream file;
	std::vector<std::vector<std::vector<int>>> world;
	std::vector<std::vector<int>> flatWorld;
	int i, j, k;

	flatWorld.resize(depth);
	for (i = 0; i < depth; ++i)
	{
		flatWorld[i].resize(width);
	}
	flatWorld[0][0] = height / 2;
	flatWorld[0][width] = height / 3;
	flatWorld[depth][0] = height / 4;
	flatWorld[depth][width] = height / 5;
	WorldGenHelper(flatWorld, 0, width, 0, depth);

	world.resize(depth);
	file.open(fileName);
	for (i = 0; i < depth; ++i)
	{
		world[i].resize(width);
		for (j = 0; j < width; ++j)
		{
			world.resize(height);
			for (k = 0; k < height; ++k)
			{
				if (k < flatWorld[i][j])
				{
					world[i][j][k] = 1;
				}
				else if(k > flatWorld[i][j])
				{
					world[i][j][k] = 0;
				}
				else
				{
					world[i][j][k] = 2;
				}
			}
		}
	}
	file << height << COMMA << width << COMMA << depth << std::endl;
	for (i = 0; i < depth; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			for (k = 0; k < height; ++k)
			{
				file << world[i][j][k];
				if (k != height)
				{
					file << COMMA;
				}
				else
				{
					file << std::endl;
				}
			}
		}
		if (i != height)
		{
			file << std::endl;
		}
	}
}
