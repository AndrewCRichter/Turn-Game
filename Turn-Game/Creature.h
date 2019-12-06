#pragma once
#include "RenderableEntity.h"

class Creature :
	public RenderableEntity
{
private:
    const float gravity = 1;
    float width = 1, height = 1;
    float x;
    float y;
    float dx, dy;
    int x0;
    int z0;
    Direction currentDir;
    std::vector<std::vector<int>> currentSlice;
    sf::Texture* spritesheet;
public:
	Creature();
    Creature(sf::Texture* spritesheet, float x, float y, int x0, int z0, Direction dir, std::vector<std::vector<int>> slice);
    void move(float x, float y);
    void setVelocity(float dx, float dy);
	void processPhysics(float dt);
    float getX();
    float getY();
    int * getXZ(int * xz);
    Direction getDirection();
    float getOffset();
};

