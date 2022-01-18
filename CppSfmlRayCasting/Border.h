#ifndef BORDER_H
#define BORDER_H

#include "Utils.h"
#include "Settings.h"

#include <SFML/Graphics.hpp>

namespace gst {
	class Border
	{
	public:
		Border();
		Border(sf::Vector2f point, Direction direction);

		void nextPoint();

		Direction _direction = Direction::NONE;
		sf::Vector2f _point;
		float _delta = PLAYER_RADIUS;
		float _temp_delta = 0.0f;
		bool _collision = false;
	};
}

#endif // !BORDER_H