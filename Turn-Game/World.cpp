#include "World.h"
#include "LiveTilemap.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

int World::WorldGenVal(int x, int y)
{
	return std::rand() % (int)(1.5 * (x < y ? y - x : x - y)) + x < y ? x : y;
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

World::World(std::string fileName)
{
	const std::string SEP = "\n",
				COMMA = ",";
	int height,
		width,
		depth,
		next,
		tileHeight,
		tileWidth,
		tilesPerRow;
	bool iRow,
		jRow,
		kRow;
	bool good = true;
	int i, j, k;
	std::string ascii;
	std::ifstream inputWorld;
	sf::Texture worldTxtures;
	inputWorld.open(fileName);
    std::string texfile;
    std::getline(inputWorld, texfile);
	if (inputWorld.bad() || !worldTxtures.loadFromFile(texfile))
	{
		std::cerr << "FAILED LOADING WORLD TEXTURE: " << texfile << "\n";
	}
	inputWorld >> tileHeight >> ascii >> tileWidth >> ascii >> tilesPerRow >> ascii;
	this->tiles = { &worldTxtures, tileHeight, tileWidth, tilesPerRow };
	inputWorld >> height >> ascii >> width >> ascii >> depth >> ascii;
	if (inputWorld.good()) {
		world.resize(depth);
		for (i = 0; iRow && good; ++i)
		{
			world[i].resize(width);
			jRow = true;
			for (j = 0; jRow && good; ++j)
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
void World::WorldGen(std::string fileName, int height, int width, int depth, int cut, std::string pngFile, int tileHeight, int tileWidth, int tilesPerRow)
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
				if (i == j + cut || i == j - cut)
				{
					world[i][j][k] = -1;
				}
				else if (k < flatWorld[i][j])
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
	file << pngFile << std::endl;
	file << tileHeight << COMMA << tileWidth << COMMA << tilesPerRow << std::endl;
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

sf::Color getColor(int depth) {
    if (depth == 1) return sf::Color((sf::Uint8)(255/std::sqrt(depth)), (sf::Uint8)(255/std::sqrt(depth)), 255);
    if (depth > 0) return sf::Color(255/depth, 255/ depth, 255);
    return sf::Color(255, 255, 255, (sf::Uint8)(255.0/(depth+1)));
}

void drawWorld(sf::RenderTarget & rt, World w, std::vector<RenderableEntity*> entities, int x, int z, Direction d) {drawWorld(rt, w,entities, x, z, d, sf::Transform());}

void drawWorld(sf::RenderTarget & rt, World w, std::vector<RenderableEntity*> entities, int x, int z, Direction d, sf::Transform transform)
{
    std::vector<sf::Drawable*> drawObjects;
    std::vector<float> offsets, heights,depths;

    int offs = 0, depth;
    Direction frontDirection = (Direction)((d+1) %6);
    const int* fdp = DIRECTION_VALUES[frontDirection];
    int max = 1;
    for(;offs >= 0; max++)w.getSlice(x + max * fdp[0], z + max * fdp[1], d, &depth);
    for (max--; max > 0; max--) {
        LiveTilemap next(w.getTileset());
        std::vector<std::vector<int>> sheet = w.getSlice(x + max * fdp[0], z + max * fdp[1], d, &offs);
        if (offs >= 0) {
            next.update(sheet, getColor(max));
            drawObjects.push_back(&next);
            offsets.push_back(offs);
            depths.push_back(max);
            heights.push_back(0);

            for (unsigned int e = 0; e < entities.size(); e++) {
                float eoffs;
                float depth = entities[e]->getDepth(x, z, d, &eoffs);
                if ((int) depth == max) {
                    drawObjects.push_back(entities[e]);
                    offsets.push_back(eoffs);
                    depths.push_back(depth);
                    heights.push_back(entities[e]->getY());
                }
            }
        }
    }
    Direction backDirection = (Direction)((d + 5) % 6);//The direction away from the camera is the first counterclockwise direction in the enum.
    const int* dp = DIRECTION_VALUES[backDirection];
    float baseOffs;
    for (int i = 0; offs >= 0; i++) { //Going back.
        LiveTilemap next(w.getTileset());
        std::vector<std::vector<int>> sheet = w.getSlice(x + i * dp[0], z + i * dp[1], d, &offs);
        if (i == 0) baseOffs = (float) offs;
        if (offs >= 0) {
            next.update(sheet, getColor(i));
            drawObjects.push_back(&next);
            offsets.push_back(offs);
            depths.push_back(i);
            heights.push_back(0);

            for (unsigned int e = 0; e < entities.size(); e++) {
                float eoffs,
                     depth = entities[e]->getDepth(x, z, d, &eoffs);
                if ((int) depth == i) {
                    drawObjects.push_back(entities[e]);
                    offsets.push_back(eoffs);
                    depths.push_back(depth);
                    heights.push_back(entities[e]->getY());
                }
            }
        }
    }
    for (int i = offsets.size() - 1; i >= 0; i--) { //Draw the planes back-to-front.
        sf::Transform translation;
        translation.translate(w.getTileset().tileWidth*(std::abs(depths[i]) / 2.0f + baseOffs - offsets[i]), heights[i]);
        rt.draw(*drawObjects[i], translation * transform);
    }
}