#include "Creature.h"



Creature::Creature()
{
}

Creature::Creature(sf::Texture* spritesheet, float x, float y, int x0, int z0, Direction dir, std::vector<std::vector<int>> slice)
{
	this->x = x;
	this->y = y;

	this->x0 = x0;
	this->z0 = z0;
	this->currentDir = dir;
	this->currentSlice = slice;
	this->spritesheet = spritesheet;
}
void Creature::move(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Creature::setVelocity(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

void Creature::processPhysics(float dt)
{
	dy += dt * gravity;
	//Check collision with terrain

	float scale = std::sqrt(dx * dx + dy * dy);

	float minDist = -1;
	bool anyhit = false, hitX = false;
	for (int xoff = -1; xoff < 2; xoff += 2)
		for (int yoff = -1; yoff < 2; yoff++) {
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
	if (anyhit) {
		x += minDist * dx;
		y += minDist * dy;
		if (hitX)
			dx = 0;
		else { //We hit ground
			dy = 0;
		}

	}
	else {
		//No collisions
		x += dx * dt;
		y += dy * dt;
	}
}


float Creature::getX()
{
	return x;
}
float Creature::getY()
{
	return y;
}
int* Creature::getXZ(int* xz)
{
	xz[0] = (int)(x0 + x * DIRECTION_VALUES[currentDir][0]);
	xz[1] = (int)(z0 + x * DIRECTION_VALUES[currentDir][1]);
	return xz;
}
Direction Creature::getDirection()
{
	return currentDir;
}
float Creature::getOffset()
{
	return x - std::round(x);
}