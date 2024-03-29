#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include <SFML/Graphics.hpp>

namespace gst {

	static const bool			SHOW_DEBUG			= false;
	static const bool			STOP_AT_END			= false;

	static const unsigned		WINDOW_WIDTH		= 800;
	static const unsigned		WINDOW_HEIGHT		= 400;
	static const std::string	WINDOW_TITLE		= "CPP_SFML";
	static const sf::Color		WINDOW_BACK_COLOR	= sf::Color(150, 150, 150);

	static const std::string	MAP_FILE_LOCATION	= "map_1.bmp";
	static const float			WORLD_BLOC_SIZE		= 10.0f;

	static const float			PLAYER_RADIUS		= 5.0f;
	static const float			PLAYER_SPEED		= 1.5f; // displacement speed in [px/frame]
	static const float			ROTATION_SPEED		= 2.0f; // rotation speed in [deg/frame]

	static const unsigned		TIME_PER_FRAME		= 10; // diff time [ms] between two computations

	static const float			PI					= 3.14159265359f;

	static const float			FIELD_OF_VIEW		= 60.0f;
	static const float			RAY_DIFF_ANGLE		= FIELD_OF_VIEW / WINDOW_WIDTH;
	static const float			DEPTH_OF_VIEW		= 300.0f;
	static const float			RENDER_DISTANCE		= 250.0f;


	enum class WorldBlocType {
		BACKGROUND = 0,
		FLOOR
	};
}

#endif //SETTINGS_H
