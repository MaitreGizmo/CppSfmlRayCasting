#include "Utils.h"
#include "Settings.h"

#include <SFML/Graphics.hpp>

using namespace gst;
using namespace std;
using namespace sf;

float Utils::degToRad(float deg)
{
	return deg * PI / 180.0f;
}

float Utils::radToDeg(float rad) {
	return 180.0f * rad / PI;
}

float Utils::getDelta(Vector2f& point_a, Vector2f& point_b) {
	float delta_x = abs(point_a.x - point_b.x);
	float delta_y = abs(point_a.y - point_b.y);

	float dist = sqrt(pow(delta_x, 2.0f) + pow(delta_y, 2.0f));

	return dist;
}
