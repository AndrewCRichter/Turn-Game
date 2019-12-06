#pragma once

#include "Direction.h"
#include <SFML/Graphics.hpp>

class RenderableEntity : public sf::Drawable, public sf::Transformable
{
public:
    int* getXZ(int* xz);      //Position of the creature within the world.
    float getY();             //Y position of the creature
    int getXOffset();         //Distance away from the XZ position the creature is.
    Direction getDirection(); //Direction of the offset/slice the creature is in
    float getDepth(int x, int z, Direction dir, float* offset); //Given a slice in direction dir containing the cell (x,z), how far is it from that slice, perpendicularly?
    void draw(sf::RenderTarget& rt, sf::RenderStates states);
};