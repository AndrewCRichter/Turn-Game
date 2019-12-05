#pragma once
#ifndef THING
#define THING

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tileset.h"
#include "Direction.h"


class World
{
private:
	const int EMPTY = -1;
	int height;
	int width;
	int depth;
	std::vector<std::vector<std::vector<int>>> world;
    Tileset tiles;
	int WorldGenVal(int x, int y);
	void WorldGenHelper(std::vector<std::vector<int>> &world, int xStart, int xEnd, int zStart, int zEnd);
    
public:
	World(std::string fileName); //TODO: Move texture directory into file.
    World(std::vector<std::vector<std::vector<int>>> world, Tileset ts, int height, int width, int depth);
	std::vector<std::vector<int>> getSlice(int x, int z, Direction d, int* offset);
	void WorldGen(std::string fileName, int height, int width, int depth, int cut, std::string pngFile, int tileHeight, int tileWidth, int tilesPerRow);
    Tileset getTileset();
};

void drawWorldOpaque(sf::RenderTarget &rt, World w, int x, int z, Direction d);
void drawWorldOpaque(sf::RenderTarget &rt, World w, int x, int z, Direction d, sf::Transform transform);


#endif // THING