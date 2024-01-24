#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:

	Snake() = default;

	Snake(int dim);

	void move();

	void turn(bool left);

	sf::Vector2i& getHead();

	int getDirection();

	std::vector<sf::Vector2i>& getBody();

	bool checkSelf();

	void growNext();
protected:
private:
	std::vector<sf::Vector2i> body; // Snake coords { Head, body 1, body 2, ... }
	int direction;	// 0 == Up, 1 == Right, 2 == Down, 3 == Left

	bool grow;
};

inline Snake::Snake(int dim) {
	body.push_back(sf::Vector2i(1, dim / 2));
	body.push_back(sf::Vector2i(0, dim / 2));

	direction = 1;
}

inline void Snake::move() {
	if (!grow) {
		// Shift backwards
		for (int i = body.size() - 1; i > 0; --i) {
			body[i] = body[i - 1];
		}
	}
	else {
		
		body.insert(body.begin() + 1, body[0]);

		grow = false;
	}
	

	if (direction == 0) { --body[0].y; }
	else if (direction == 1) { ++body[0].x; }
	else if (direction == 2) { ++body[0].y; }
	else { --body[0].x; }
}

inline void Snake::turn(bool left) {
	if (left) {
		--direction;
		if (direction < 0) { direction = 3; }
	}
	else {
		++direction;
		if (direction > 3) { direction = 0; }
	}
}

inline sf::Vector2i& Snake::getHead() {
	return body[0];
}

inline int Snake::getDirection() {
	return direction;
}

inline std::vector<sf::Vector2i>& Snake::getBody() {
	return body;
}

inline bool Snake::checkSelf() {
	for (int i = 0; i < body.size(); ++i) {
		for (int ii = 0; ii < body.size(); ++ii) {
			if (i == ii) { continue; }
			if (body[i] == body[ii]) { return true; } // Self Collision
		}
	}

	return false;
}

inline void Snake::growNext() {
	grow = true;
}

#endif // SNAKE_HPP
