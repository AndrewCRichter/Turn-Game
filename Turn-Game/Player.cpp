#include "Player.h"
#include "Tileset.h"
#include "LiveTilemap.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Player::Player(sf::Texture* spritesheet, float x, float y, int x0, int z0, Direction dir, std::vector<std::vector<int>> slice)
{
	this->x = x;
	this->y = y;

	this->x0 = x0;
	this->z0 = z0;
	this->currentDir = dir;
	this->currentSlice = slice;
	this->canJump = false;
	this->spritesheet = spritesheet;
}
void Player::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Player::setVelocity(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}


int Player::getCorner(int xoff, int yoff) {
	int xp = (int)(x + xoff *  width / 2),
		yp = (int)(y + yoff * height / 2);
	if (0 > xp || xp > (int)currentSlice.size()
		|| 0 > yp || yp > (int)currentSlice[0].size())
		return -1;
	return currentSlice[xp][yp];
}

void Player::processPhysics(float dt)
{
	dy += dt * gravity;
	//Check collision with terrain

	float scale = std::sqrt(dx * dx + dy * dy);

	float minDist = -1;
	bool anyhit=false, hitX=false;
	for (int xoff = -1; xoff < 2; xoff += 2)
		for (int yoff = 0; yoff < 3; yoff++) {
			float xp = x + xoff * width / 2,
				yp = y + yoff * height / 2;
			float totalDist = 0;
			bool hit = false;
			bool xLeft = dx < 0,
				yDown = dy < 0;
			while (totalDist < dt && !hit) {
				int targetX = (int)(xp + (xLeft ? -1 : 1)),
					targetY = (int)(yp + (yDown ? -1 : 1));
				float xdis = (targetX - xp) / dx, ydis = (targetY - yp) / dy;

				int block;
				bool tempHitX = false;

				if (xdis < ydis) {//We hit a vertical line first

					block = currentSlice[targetX][(int)yp];

					xp += dx * xdis;
					yp += dy * xdis;
					totalDist += xdis;
					tempHitX = true;
				}
				else { //we hit a horizontal line first
					block = currentSlice[(int)xp][targetY];
					xp += dx * ydis;
					yp += dy * ydis;
					totalDist += ydis;

				}

				if (block > 0) {
					hit = true;
					anyhit = true;
					if (!anyhit || minDist > totalDist) {
						minDist = totalDist;
						hitX = tempHitX;
					}
					break;
				}

			}
		}
	canJump = false; //We can't jump by default.
	if (anyhit) { 
		x += minDist * dx;
		y += minDist * dy;
		if (hitX)
			dx = 0;
		else{ //We hit ground
			canJump = true;
			dy = 0;
		}
	}
	else {
		//No collisions
		x += dx * dt;
		y += dy * dt;
	}
}


float Player::getX()
{
	return x;
}
float Player::getY()
{
	return y;
}
int* Player::getXZ(int* xz)
{
    xz[0] = (int)(x0 + x * DIRECTION_VALUES[currentDir][0]);
    xz[1] = (int)(z0 + x * DIRECTION_VALUES[currentDir][1]);
    return xz;
}
Direction Player::getDirection()
{
    return currentDir;
}
float Player::getOffset()
{
	return x - std::round(x);
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    //states.texture = tiles.tileTextures;
    sf::RectangleShape pRect(sf::Vector2f(width,height));
    pRect.setTexture(spritesheet);
    target.draw(pRect,states);
    //Draw the player
}

/*void drawPlayer(sf::RenderTarget &rt, Player p, sf::Transform transform) //Note that transform is applied last.
{
    int xz[2];
    int offs;
    Direction dir;
    p.getXZ(xz);
    dir = p.getDirection();
    //Draw opaque layers, starting with the current layer.
    Tileset t = w.getTileset();



}*/
