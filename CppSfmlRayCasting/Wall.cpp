#include "Wall.h"

using namespace gst;
using namespace std;
using namespace sf;

Wall::Wall() = default;

Wall::Wall(Vector2f origin) {
	_origin = origin;
	_destination = origin;
}

Vector2f Wall::getOrigin() {
	return _origin;
}

Vector2f Wall::getDestination() {
	return _destination;
}

void Wall::setDestination(Vector2f destination) {
	_destination = destination;
}