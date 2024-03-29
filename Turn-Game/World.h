#pragma once
#ifndef THING
#define THING

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tileset.h"
#include "Direction.h"
#include "RenderableEntity.h"

class World
{
private:
	const int EMPTY = -1;
	int height;
	int width;
	int depth;
	std::vector<std::vector<std::vector<int>>> world;
    Tileset tiles;
    static int WorldGenVal(int x, int y);
    static void WorldGenHelper(std::vector<std::vector<int>> &world, int xStart, int xEnd, int zStart, int zEnd);
    
public:
	World(std::string fileName); //TODO: Move texture directory into file.
    World(std::vector<std::vector<std::vector<int>>> world, Tileset ts, int height, int width, int depth);
	std::vector<std::vector<int>> getSlice(int x, int z, Direction d, int* offset);
	static void WorldGen(std::string fileName, std::string pngFile, int height, int width, int depth, int cut, int tileHeight, int tileWidth, int tilesPerRow);
    Tileset getTileset();
};

sf::Color getColor(int depth);

void drawWorld(sf::RenderTarget &rt, World w, std::vector<RenderableEntity*> entities, int x, int z, Direction d);
void drawWorld(sf::RenderTarget &rt, World w, std::vector<RenderableEntity*> entities, int x, int z, Direction d, sf::Transform transform);


#endif // THING