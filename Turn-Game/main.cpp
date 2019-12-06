#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "LiveTilemap.h"
#include "World.h"
#include "Player.h"
#include "main.h"

int main() {
	World::WorldGen("Test World", "Test Texture", 64, 64, 64, 64, 64, 64, 3);
	
	sf::RenderWindow window(sf::VideoMode(500, 500), "AAAAA");
	sf::Clock timer;
	sf::Time elapsed;
	//INIT
	sf::Texture txt;
	std::string filen = "TestTexture.png";
	if (!txt.loadFromFile(filen)) {
		std::cerr << "FAILED READING WORLD TEXTURE\n";
	}

    sf::Texture playerTex;
    if (!playerTex.loadFromFile("Player.png")) {
        std::cerr << "FAILED READING PLAYER TEXTURE\n";
    }

    Tileset t = { &txt, 16, 16, 2 };
	LiveTilemap l(t);
	txt.setSmooth(false);

	//Temp map & player testing stuff
	int MAP_X = 11, MAP_Y = 10;
	std::vector<std::vector<std::vector<int>>> map;
    map.resize(2);
    map[0].resize(MAP_X);
    map[1].resize(MAP_X);
	for (int x = 0; x < MAP_X; x++) {
		map[0][x].resize(MAP_Y);
        map[1][x].resize(MAP_Y);
		for (int y = 0; y < MAP_Y; y++) {
            if (y < 3)map[1][x][y] = 4;
            else if (y >= 4) map[1][x][y] = 0;

			if (x >= MAP_Y) {
				if (y == MAP_Y - 1)
					map[0][x][y] = 2;
				else map[0][x][y] = 4;
			}
			else {
				if (x == y)
					map[0][x][y] = 1;
				else if (y == x - 1)
					map[0][x][y] = 3;
				else map[0][x][y] = y < x ? 4 : 0;
			}
		}
	}
	//std::vector<int> a; a.push_back(2); a.push_back(0); a.push_back(0);
	///std::vector<int> b; b.push_back(3); b.push_back(1); b.push_back(0);
	//std::vector<int> c; c.push_back(4); c.push_back(3); c.push_back(1);
	//map.push_back(a);
	//map.push_back(b);
	//map.push_back(c);
	//l.update(map);

	sf::Transform trans;
	trans.translate(20, 500).scale(2, -2);

    World w(map, t, map[0][0].size(), map.size(), map[0].size());
    int offs = 0;
    std::vector<std::vector<int>> slice = w.getSlice(0, 0, Direction::DOWN, &offs);
    Player p(&playerTex, 0.5, 3, 0, 0, Direction::DOWN, slice);
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
        int xz[2];
        p.getXZ(xz);
        std::vector<RenderableEntity*> entities;
        entities.push_back((RenderableEntity*) &p);
        drawWorld(window, w, entities, xz[0],xz[1],p.getDirection());
        //window.draw(l, trans);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        window.draw(sf::CircleShape(10, 10),sf::Transform().translate(window.mapPixelToCoords(mousePos)));
		window.display();

	}
	
	return 0;
}