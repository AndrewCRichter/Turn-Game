#pragma once
#include <SFML/Graphics/Texture.hpp>

struct Tileset {
    const sf::Texture* tileTextures;
    int tileWidth, tileHeight, tilesPerRow;
};
