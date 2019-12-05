#pragma once
#ifndef TURN_GAME_PLAYER_H
#define TURN_GAME_PLAYER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "World.h"

class Player
{
private:
	const float gravity = 1;
	const float width = .875f,
			   height = 1.875f;
	float x;
	float y;
	float dx, dy;
	int x0;
	int z0;
	Direction currentDir;
	std::vector<std::vector<int>> currentSlice;
	sf::Texture* spritesheet;
	bool canJump; //True if the player is touching ground.

	int getCorner(int xoff, int yoff);

public:
	Player(sf::Texture* spritesheet, float x, float y, int x0, int z0, Direction dir, std::vector<std::vector<int>> slice);
	void move(float x, float y); //Teleports the player.
	void setVelocity(float dx, float dy); //Sets the player's velocity.
	void processPhysics(float dt); //Processes one step of physics. Applies gravity and checs for collisions before moving the player.
	float getX(); //Get the in-slice X position of the player.
	float getY(); //Get the in-slice Y position of the player.
	int* getXZ(int* xz); //Gets the world XZ position of the player. Input is a pointer to an array of size 2.
    Direction getDirection();
	float getOffset(); //Gets player's offset from the nearest block.
};

//Draws a player to the screen
void drawPlayer(sf::RenderTarget &rt, Player p, World w);
void drawPlayer(sf::RenderTarget &rt, Player p, World w,sf::Transform transform);

#endif //TURN_GAME_PLAYER_H