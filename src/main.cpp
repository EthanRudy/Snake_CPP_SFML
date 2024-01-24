#include <iostream>
#include "../include/Game.hpp"

int main() {
	srand(time(NULL));

	Game game(sf::Vector2f(1000, 1000), 17);

	game.run();
}