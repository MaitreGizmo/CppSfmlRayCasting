#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

namespace gst {
	class Utils {
	public:
		static float degToRad(float deg);
		static float radToDeg(float rad);

		static float getDelta(sf::Vector2f& point_a, sf::Vector2f& point_b);
	};

	enum class Direction {
		NONE = 0,

		TOP,
		BOTTOM,
		LEFT,
		RIGHT,

		FORWARD,
		BACKWARD
	};

}

#endif // !UTILS_H
