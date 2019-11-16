#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "LiveTilemap.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "AAAAA");
	sf::Clock timer;
	sf::Time elapsed;
	//INIT
	sf::Texture txt;
	std::string filen = "TestTexture.png";
	if (! txt.loadFromFile(filen));
	LiveTilemap l(&txt,16,16,2);

	std::vector<std::vector<int>> map;
	std::vector<int> a; a.push_back(2); a.push_back(0);
	std::vector<int> b; b.push_back(3); b.push_back(1);
	map.push_back(a);
	map.push_back(b);
	
	l.update(map,64,64);

	sf::Transform trans;
	trans.translate(250, 250).scale(1, -1);

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