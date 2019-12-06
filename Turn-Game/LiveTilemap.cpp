#include "LiveTilemap.h"
#include <vector>

LiveTilemap::LiveTilemap(Tileset t)
{
	this->tiles = t;
	verts.setPrimitiveType(sf::Quads);
}

bool LiveTilemap::update(const std::vector<std::vector<int>> &sheet, sf::Color tint)
{
	int width  = sheet.size(),
		height = sheet[0].size();
    this->verts.resize(width*height * 4);//Set the vert array to be the right size
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++) {
            int t_id = sheet[i][j];
			if (t_id < 0)return false;

			int tu = t_id % tiles.tilesPerRow,
				tv = t_id / tiles.tilesPerRow;

			sf::Vertex* quadIndex = &(this->verts[(i + j * width) * 4]);
			
			quadIndex[0].position = sf::Vector2f((float)      i*tiles.tileWidth, (float)      j*tiles.tileHeight);
			quadIndex[1].position = sf::Vector2f((float)(i + 1)*tiles.tileWidth, (float)      j*tiles.tileHeight);
			quadIndex[2].position = sf::Vector2f((float)(i + 1)*tiles.tileWidth, (float)(j + 1)*tiles.tileHeight);
			quadIndex[3].position = sf::Vector2f((float)      i*tiles.tileWidth, (float)(j + 1)*tiles.tileHeight);
			
			quadIndex[3].texCoords= sf::Vector2f((float)      tu*tiles.tileWidth, (float)      tv*tiles.tileHeight);
			quadIndex[2].texCoords= sf::Vector2f((float)(tu + 1)*tiles.tileWidth, (float)      tv*tiles.tileHeight);
			quadIndex[1].texCoords= sf::Vector2f((float)(tu + 1)*tiles.tileWidth, (float)(tv + 1)*tiles.tileHeight);
			quadIndex[0].texCoords= sf::Vector2f((float)      tu*tiles.tileWidth, (float)(tv + 1)*tiles.tileHeight);
            
            quadIndex[0].color = tint;
            quadIndex[1].color = tint;
            quadIndex[2].color = tint;
            quadIndex[3].color = tint;
		}
	return true;
}

void LiveTilemap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
	states.texture = tiles.tileTextures;
	target.draw(verts, states);
}
