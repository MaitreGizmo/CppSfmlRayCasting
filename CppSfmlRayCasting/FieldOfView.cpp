#include "FieldOfView.h"

#include "WorldBloc.h"
#include "Player.h"
#include "Settings.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace gst;
using namespace std;
using namespace sf;

FieldOfView::FieldOfView() = default;

FieldOfView::FieldOfView(World * world, Player * player) {
	_world = world;
	_player = player;

	float lower_bound = -1.0f * FIELD_OF_VIEW / 2.0f;
	float upper_bound = FIELD_OF_VIEW / 2.0f;

	for (float i = lower_bound; i < upper_bound; i += RAY_DIFF_ANGLE) {
		VertexArray line(sf::LineStrip, 2);
		line[0].position = Vector2f(0, 0);
		line[1].position = Vector2f(0, 0);

		_lines.push_back(line);
	}
}

void FieldOfView::draw(RenderWindow & window) {
	for (VertexArray line : _lines) {
		window.draw(line);
	}
}

void FieldOfView::refresh() {
	Vector2f origin = _player->getPos();

	float lower_bound = -1.0f * FIELD_OF_VIEW / 2.0f;
	float upper_bound = FIELD_OF_VIEW / 2.0f;

	float player_angle = _player->getRotation();

	float player_x = _player->getPos().x;
	float player_y = _player->getPos().y;

	size_t index = 0;

	for (float i = lower_bound; i < upper_bound; i += RAY_DIFF_ANGLE) {
		float angle = player_angle + Utils::degToRad(i);

		bool collision = false;

		Vector2f destination;

		for (int j = 0; j < int(DEPTH_OF_VIEW); j += 1.0f) {
			destination.x = player_x + float(j) * cos(angle);
			destination.y = player_y + float(j) * sin(angle);

			bool collision = false;

			WorldBloc& bloc = _world->getBloc(destination);

			if (bloc.getType() != WorldBlocType::BACKGROUND) {
				collision = true;
				break;
			}
		}

		_lines[index][0].position = origin;
		_lines[index][1].position = destination;

		++index;
	}


}