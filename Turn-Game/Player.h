#pragma once
#ifndef TURN_GAME_PLAYER_H
#define TURN_GAME_PLAYER_H

class Player
{
private:
	float x;
	float y;
	int x0;
	int z0;
	int direction[2];
public:
	Player(int x, int y, int x0, int y0, const int direction[2]);
	void move(float x, float y);
	float getX();
	float getY();
	int* getXZ(int* xz);
	float getOffset();
};
#endif //TURN_GAME_PLAYER_H