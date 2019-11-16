#pragma once
#ifndef TURN_GAME_PLAYER_H
#define TURN_GAME_PLAYER_H

#include <vector>

class Player
{
private:
	const float gravity = 1;
	const float width = .8,
			   height = 1.9;
	float x;
	float y;
	float dx, dy;
	int x0;
	int z0;
	int direction[2];
	std::vector<std::vector<int>> currentSlice;
	int getCorner(int xoff, int yoff);
public:
	Player(int x, int y, int x0, int y0, const int direction[2], std::vector<std::vector<int>> slice);
	void move(float x, float y);
	void processPhysics(float dt);
	float getX();
	float getY();
	int* getXZ(int* xz);
	float getOffset();
};
#endif //TURN_GAME_PLAYER_H