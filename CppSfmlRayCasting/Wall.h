#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

namespace gst {
	class Wall
	{
	public:
		Wall();
		Wall(sf::Vector2f origin);

		sf::Vector2f getOrigin();
		sf::Vector2f getDestination();

		void setDestination(sf::Vector2f destination);

	private:
		sf::Vector2f _origin;
		sf::Vector2f _destination;
	};

}

#endif // !WALL_H