#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"

#include <SFML/Graphics.hpp>

namespace gst {
	class Player {
	public:
		Player();

		Player(sf::Vector2f initPos);

		void draw(sf::RenderWindow& window);

		void applyMove();

		float getRotation();

		void rotateLeft();
		void rotateRight();

		void moveForward();
		void stopMoveForward();

		void moveBackward();
		void stopMoveBackward();

		sf::Vector2f& getPos();

		sf::FloatRect getGlobalBounds();
		sf::FloatRect getLocalBounds();

		void moveX(float delta);
		void moveY(float delta);

		Direction getDirection();

	private:
		sf::Vector2f _position;

		float _rotation = 0.0f;
		float _speed = 0.0f;

		Direction _direction = Direction::NONE;

		sf::CircleShape _shape;
		sf::RectangleShape _line;

		void correctRotationMultiples();

	};
}


#endif //PLAYER_H
