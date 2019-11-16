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
	std::vector<int> a; a.push_back(1); a.push_back(2);
	std::vector<int> b; b.push_back(1); b.push_back(0);
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

		window.draw(l,trans);
		window.display();
		//GAME GRAPHICS HERE

		
	}

	return 0;
}