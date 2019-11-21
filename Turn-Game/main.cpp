#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "LiveTilemap.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "AAAAA");
	sf::Clock timer;
	sf::Time elapsed;
	//INIT
	sf::Texture txt;
	std::string filen = "TestTexture.png";
	if (!txt.loadFromFile(filen)) {
		std::cerr << "FAILED READING WORLD TEXTURE\n";
	}
	LiveTilemap l(&txt,16,16,2);
	txt.setSmooth(false);

	//Temp map & player testing stuff
	int MAP_X = 11, MAP_Y = 10;
	std::vector<std::vector<int>> map;
	map.resize(MAP_X);
	for (int x = 0; x < MAP_X; x++) {
		map[x].resize(MAP_Y);
		for (int y = 0; y < MAP_Y; y++) {
			if (x >= MAP_Y) {
				if (y == MAP_Y - 1)
					map[x][y] = 2;
				else map[x][y] = 4;
			}
			else {
				if (x == y)
					map[x][y] = 1;
				else if (y == x - 1)
					map[x][y] = 3;
				else map[x][y] = y < x ? 4 : 0;
			}
		}
	}
	//std::vector<int> a; a.push_back(2); a.push_back(0); a.push_back(0);
	///std::vector<int> b; b.push_back(3); b.push_back(1); b.push_back(0);
	//std::vector<int> c; c.push_back(4); c.push_back(3); c.push_back(1);
	//map.push_back(a);
	//map.push_back(b);
	//map.push_back(c);
	
	l.update(map,32,32);

	sf::Transform trans;
	trans.translate(20, 500).scale(1, -1);

	while (window.isOpen()) {
	
		elapsed = timer.restart();
		
		//HANDLE EVENTS
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		//GAME LOGIC HERE

		//GAME GRAPHICS HERE

		window.clear(sf::Color(0, 200, 200));
		window.draw(l, trans);
		window.display();

	}

	return 0;
}