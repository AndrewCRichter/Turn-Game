#include "Player.h"
#include <cmath>

Player::Player(int x, int y, int x0, int y0, const int direction[2], std::vector<std::vector<int>> slice)
{
	this->x = x;
	this->y = y;
	this->x0 = x0;
	this->z0 = z0;
	this->direction[0] = direction[0];
	this->direction[1] = direction[1];
	this->currentSlice = slice;
}
void Player::move(float x, float y)
{
	this->x += x;
	this->y += y;
}


int Player::getCorner(int xoff, int yoff) {
	int xp = (int)(x + xoff *  width / 2),
		yp = (int)(y + yoff * height / 2);
	if (0 > xp || xp > currentSlice.size()
		|| 0 > yp || yp > currentSlice[0].size())
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
		for (int yoff = -1; yoff < 2; yoff++) {
			float xp = x + xoff * width / 2,
				yp = y + yoff * height / 2;
			float totalDist = 0;
			bool hit = false;
			bool xLeft = dx < 0,
				yDown = dy < 0;
			while (totalDist < dt && !hit) {
				int targetX = xp + (xLeft ? -1 : 1),
					targetY = yp + (yDown ? -1 : 1);
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
	if (minDist != -1) {
		x += minDist * dx;
		y += minDist * dy;
		if (hitX)
			dx = 0;
		else
			dy = 0;
	}
	else {
	//Assuming no collisions
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
	xz[0] = std::round(x0 + x * direction[0]);
	xz[1] = std::round(z0 + x * direction[1]);
	return xz;
}
float Player::getOffset()
{
	return x - std::round(x);
}