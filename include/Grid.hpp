#ifndef GRID_HPP
#define GRID_HPP

#include <random>
#include "Snake.hpp"

class Grid {
public:

	Grid() = default;
	
	Grid(int dim, float cell_w);

	Grid(const Grid& o);

	bool update(int dir);

	void draw(sf::RenderWindow& window);

protected:
private:
	int _dim;
	float _cell_w;

	std::vector<bool> _cells;
	Snake _snake;

	int to_index(int x, int y);
};


inline Grid::Grid(int dim, float cell_w) {
	_dim = dim;
	_cell_w = cell_w;

	_cells.resize(_dim * _dim, false);

	// Generate one random fruit;
	_cells[rand() % (_dim * _dim)] = true;

	_snake = Snake(_dim);
}

inline Grid::Grid(const Grid& o) {
	_dim = o._dim;

	_cells.clear();

	for (auto i : o._cells) {
		_cells.push_back(i);
	}
}

inline bool Grid::update(int dir) {

	// Change direction
	int _direction = _snake.getDirection();
	sf::Vector2i head = _snake.getHead();
	std::vector<sf::Vector2i>& body = _snake.getBody();

	if (body.size() == _dim * _dim) { return false; }

	int ind = to_index(head.x, head.y);


	int left = _direction - 1;
	if (left < 0) { left = 3; }

	int right = _direction + 1;
	if (right > 3) { right = 0; }

	if (dir == left) {
		_snake.turn(true);
	}
	else if (dir == right) {
		_snake.turn(false);
	}
	// No else, either same dir or reverse

	// Check self collision
	if (_snake.checkSelf()) { return false; }

	// Check edge collision
	if (head.x < 0 || head.x >= _dim) { return false; }
	if (head.y < 0 || head.y >= _dim) { return false; }


	if (_cells[ind]) {
		// Grow snake
		_cells[ind] = false;

		_snake.growNext();

		// Respawn fruit
		int n;
		bool found = false;
		while (!found) {
			found = true;
			n = rand() % (_dim * _dim);
			for (int i = 0; i < body.size(); ++i) {
				if (to_index(body[i].x, body[i].y) == n) { found = false;}
			}
		}

		_cells[n] = true;
	}
	

	// Move Snake
	_snake.move();

	return true;
}

inline void Grid::draw(sf::RenderWindow& window) {
	sf::RectangleShape cell;
	//cell.setOutlineThickness(2);
	//cell.setOutlineColor(sf::Color(0, 100, 0));
	cell.setSize(sf::Vector2f(_cell_w, _cell_w));

	std::vector<sf::Vector2i> body = _snake.getBody();

	for (int y = 0; y < _dim; ++y) {
		for (int x = 0; x < _dim; ++x) {
			cell.setPosition(x * _cell_w, y * _cell_w);
			if (_cells[to_index(x, y)]) {
				cell.setFillColor(sf::Color(150, 0, 0));
			}
			else {
				if ((x + y) % 2 == 0) {
					cell.setFillColor(sf::Color(0, 175, 0));
				}
				else {
					cell.setFillColor(sf::Color(0, 150, 0));
				}
				
			}

			window.draw(cell);
		}
	}

	bool first = true;
	for (auto i : body) {
		cell.setPosition(i.x * _cell_w, i.y * _cell_w);
		cell.setFillColor(sf::Color(50, 75, 200));

		if (first) {
			first = false;
			cell.setFillColor(sf::Color(0, 50, 255));
		}

		window.draw(cell);
	}
	
}

inline int Grid::to_index(int x, int y) {
	return (_dim * y + x);
}

#endif // GRID_HPP