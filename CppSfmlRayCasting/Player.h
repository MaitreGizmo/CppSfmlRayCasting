#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace gst {
	class Player {
	public:
		Player();

		Player(sf::Vector2f initPos);

		void draw(sf::RenderWindow& window);

		void applyMove();

		void rotateLeft();
		void rotateRight();

		void moveForward();
		void stopMoveForward();

	private:
		sf::Vector2f _position;

		float _rotation = 0.0f;
		float _speed = 0.0f;

		sf::CircleShape _shape;
		sf::RectangleShape _line;

		void correctRotationMultiples();

	};
}


#endif //PLAYER_H
