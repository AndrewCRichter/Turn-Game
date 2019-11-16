#include "Player.h"
#include <cmath>
Player::Player(int x, int y, int x0, int y0, const int direction[2])
{
	this->x = x;
	this->y = y;
	this->x0 = x0;
	this->z0 = z0;
	this->direction[0] = direction[0];
	this->direction[1] = direction[1];
}
void Player::move(float x, float y)
{
	this->x += x;
	this->y += y;
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