#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "WorldBloc.h"
#include "Player.h"
#include "Utils.h"
#include "Border.h"
#include "FieldOfView.h"
#include "World.h"

namespace gst {

	class MainWindow {
	public:
		MainWindow(unsigned width, unsigned height, const std::string& title);

		void render();

	private:
		unsigned _width;
		unsigned _height;
		std::string _title;
		sf::RenderWindow _window;
		sf::RenderWindow _window_3d;

		World _world;
		Player _player;
		FieldOfView _fieldOfView;

		void dispatchEvents();

		void displayFrame();

		void checkForKeyboardKeyPressed();

		void detectCollisions();

		bool playerIntersects(WorldBloc& bloc, Border& return_border);
		
	};

}

#endif
