#pragma once

#include <SFML/Graphics.hpp>

class LiveTilemap : public sf::Drawable, public sf::Transformable
{
public:
	
	LiveTilemap(const sf::Texture* tileset, int tileWidth, int tileHeight,int tilesPerRow);
	bool update(std::vector<std::vector<int>> tiles, float width, float height);
	
private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::Texture* tileset;
	sf::VertexArray verts;
	int t_width, t_height, perRow;

};