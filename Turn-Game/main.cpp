#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main() {
	sf::Window window(sf::VideoMode(500, 500), "AAAAA");
	sf::Clock timer;
	sf::Time elapsed;
	
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

		
	}

	return 0;
}