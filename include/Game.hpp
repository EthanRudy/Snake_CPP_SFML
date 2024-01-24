#ifndef GAME_HPP
#define GAME_HPP

#include "Grid.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:

	Game(const sf::Vector2f& window_dim, int grid_dim);

	void run();

protected:
private:

	sf::RenderWindow _window;
	int _dim;

	// Grid (snake included)
	Grid _grid;
};

inline Game::Game(const sf::Vector2f& window_dim, int grid_dim) {
	_window.create(sf::VideoMode(window_dim.x, window_dim.y), "Snake SFML C++");
	_window.setFramerateLimit(7);

	_dim = grid_dim;

	_grid = Grid(_dim, window_dim.x / _dim);

}

inline void Game::run() {

	int input_dir = 1;

	while (_window.isOpen()) {
		sf::Event e;
		while (_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) { 
				_window.close();
				return;
			}

			// Check arrow key
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				input_dir = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				input_dir = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				input_dir = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				input_dir = 3;
			}
		}

		_window.clear(sf::Color::Blue);

		if (!_grid.update(input_dir)) { 
			return; 
		}
		_grid.draw(_window);

		_window.display();
	}

	return;
}

#endif // GAME_HPP