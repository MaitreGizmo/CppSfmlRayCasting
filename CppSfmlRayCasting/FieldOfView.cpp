#include "FieldOfView.h"

#include "WorldBloc.h"
#include "Player.h"
#include "Settings.h"
#include "Utils.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <map>

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
		VertexArray ray(sf::LineStrip, 2);
		ray[0].position = Vector2f(0, 0);
		ray[1].position = Vector2f(0, 0);

		_rays.push_back(ray);

		VertexArray line(sf::LineStrip, 2);
		line[0].position = Vector2f(0, 0);
		line[1].position = Vector2f(0, 0);

		_lines.push_back(line);
	}


}

void FieldOfView::drawRays(RenderWindow & window) {
	for (VertexArray line : _rays) {
		window.draw(line);
	}
}

void FieldOfView::draw3dRender(RenderWindow & window) {
	unsigned nb_lines = _rays.size();
	static float line_width = WINDOW_WIDTH / (FIELD_OF_VIEW / RAY_DIFF_ANGLE);

	vector<float> distances(nb_lines, 0.0f);

	for (unsigned i = 0; i < nb_lines; ++i) {
		float delta_x = _rays[i][1].position.x - _rays[i][0].position.x;
		float delta_y = _rays[i][1].position.y - _rays[i][0].position.y;

		distances[i] = sqrt(pow(delta_x, 2.0f) + pow(delta_y, 2.0f));
	}

	float min_dist = *min_element(distances.begin(), distances.end());
	float max_dist = *max_element(distances.begin(), distances.end());

	float delta_dist = max_dist - min_dist;

	float alpha_width = delta_dist / 255.0f;

	for (unsigned i = 0; i < nb_lines; ++i) {
		if (distances[i] <= RENDER_DISTANCE) {
			if (_world->getBloc(Vector2f(_rays[i][1].position.x, _rays[i][1].position.y)).getType() != WorldBlocType::BACKGROUND) {
				float alpha_variation = distances[i] * alpha_width;

				alpha_variation = 255.0f - alpha_variation;

				Color color(0, 255, 0, int(alpha_variation));

				float delta_height = (distances[i] * WINDOW_HEIGHT) / DEPTH_OF_VIEW;

				float line_height = WINDOW_HEIGHT - delta_height;

				_lines[i][0].position = Vector2f(i * line_width, delta_height / 2.0f);
				_lines[i][1].position = Vector2f(i * line_width, (delta_height / 2.0f) + line_height);

				_lines[i][0].color = color;
				_lines[i][1].color = color;

				window.draw(_lines[i]);
			}
		}
	}

	VertexArray render3d;
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

		_rays[index][0].position = origin;
		_rays[index][1].position = destination;

		++index;
	}
}