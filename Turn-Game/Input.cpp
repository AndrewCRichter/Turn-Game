#include <SFML/Window/Keyboard.hpp>

enum Key
{
	RIGHT,
	LEFT,
	TURN_RIGHT,
	TURN_LEFT,
	JUMP,
	INTERACT,
	LOOK_UP,
	LOOK_DOWN
};

void readKeys(bool* keys)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		keys[LEFT] = true;
	}
	else
	{
		keys[LEFT] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		keys[RIGHT] = true;
	}
	else
	{
		keys[RIGHT] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		keys[TURN_LEFT] = true;
	}
	else
	{
		keys[TURN_LEFT] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		keys[TURN_RIGHT] = true;
	}
	else
	{
		keys[TURN_RIGHT] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		keys[JUMP] = true;
	}
	else
	{
		keys[JUMP] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		keys[INTERACT] = true;
	}
	else
	{
		keys[INTERACT] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		keys[LOOK_UP] = true;
	}
	else
	{
		keys[LOOK_UP] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		keys[LOOK_DOWN] = true;
	}
	else
	{
		keys[LOOK_DOWN] = false;
	}
}