#ifndef WORLD_H
#define WORLD_H

#include "WorldBloc.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace gst {
	class World
	{
	public:
		World();

		void loadMap(const std::string& path);

		WorldBloc& getBloc(sf::Vector2i pos);

		WorldBloc& getBloc(sf::Vector2f pos);

		std::vector<WorldBloc>& getBlocs();

		int getWidth();
		int getHeight();
	private:
		std::vector<std::vector<WorldBloc>> _mappedWorld;
		std::vector<WorldBloc> _blocs;

		int _width = 0;
		int _height = 0;
	};
}

#endif // !WORLD_H