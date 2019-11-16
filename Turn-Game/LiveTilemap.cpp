#include "LiveTilemap.h"
#include <vector>


LiveTilemap::LiveTilemap(const sf::Texture* tileset, int tileWidth, int tileHeight, int tilesPerRow)
{
	this->tileset = tileset;
	this->t_width = tileWidth;
	this->t_height = tileHeight;
	this->perRow = tilesPerRow;
	verts.setPrimitiveType(sf::Quads);
}

bool LiveTilemap::update(std::vector<std::vector<int>> tiles, float tileWidth, float tileHeight)
{
	int width  = tiles.size(),
		height = tiles[0].size();
	verts.resize(width*height * 4);//Set the vert array to be the right size
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++) {
			int t_id = tiles[i][j];

			if (t_id < 0)return false;
			
			int tu = t_id % perRow,
				tv = t_id / perRow;
			
			sf::Vertex* quadIndex = &(verts[(i + j * width) * 4]);
			
			quadIndex[0].position = sf::Vector2f((float)      i*tileWidth, (float)      j*tileHeight);
			quadIndex[1].position = sf::Vector2f((float)(i + 1)*tileWidth, (float)      j*tileHeight);
			quadIndex[2].position = sf::Vector2f((float)(i + 1)*tileWidth, (float)(j + 1)*tileHeight);
			quadIndex[3].position = sf::Vector2f((float)      i*tileWidth, (float)(j + 1)*tileHeight);
			
			quadIndex[3].texCoords= sf::Vector2f((float)      tu*t_width, (float)      tv*t_height);
			quadIndex[2].texCoords= sf::Vector2f((float)(tu + 1)*t_width, (float)      tv*t_height);
			quadIndex[1].texCoords= sf::Vector2f((float)(tu + 1)*t_width, (float)(tv + 1)*t_height);
			quadIndex[0].texCoords= sf::Vector2f((float)      tu*t_width, (float)(tv + 1)*t_height);
		}
	return true;
}

void LiveTilemap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	states.texture = tileset;
	target.draw(verts, states);
}
