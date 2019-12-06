#pragma once

#include <SFML/Graphics.hpp>
#include "Tileset.h"

class LiveTilemap : public sf::Drawable, public sf::Transformable
{
private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray verts;
    Tileset tiles;

public:
	
	LiveTilemap(Tileset t);
	bool update(const std::vector<std::vector<int>> &tiles, sf::Color tint);
};