#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>

struct Tileset {
    const sf::Texture* tileTextures;
    int tileWidth, tileHeight, tilesPerRow;
};
