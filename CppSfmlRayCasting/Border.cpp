#include "Border.h"

using namespace gst;
using namespace std;
using namespace sf;

Border::Border() = default;

Border::Border(Vector2f point, Direction direction)
{
	_direction = direction;
	_point = point;
}

void Border::nextPoint()
{
	switch (_direction) {
	case Direction::TOP:
		_point.x -= 1;
		break;
	case Direction::BOTTOM:
		_point.x += 1;
		break;
	case Direction::LEFT:
		_point.y += 1;
		break;
	case Direction::RIGHT:
		_point.y -= 1;
		break;
	}
}
