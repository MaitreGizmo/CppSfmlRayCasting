#ifndef FIELD_OF_VIEW_H
#define FIELD_OF_VIEW_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "WorldBloc.h"
#include "Player.h"
#include "World.h"

namespace gst {
	class FieldOfView
	{
	public:
		FieldOfView();
		FieldOfView(World* world, Player* player);

		void draw(sf::RenderWindow& window);

		void refresh();

	private:
		World* _world = nullptr;
		Player* _player = nullptr;

		std::vector<sf::VertexArray> _lines;


	};
}

#endif // !FIELD_OF_VIEW_H