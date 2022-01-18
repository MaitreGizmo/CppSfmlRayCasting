#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

#include "MainWindow.h"
#include "Settings.h"
#include "Utils.h"
#include "Border.h"

using namespace std;
using namespace std::chrono;
using namespace gst;
using namespace sf;

MainWindow::MainWindow(unsigned width, unsigned height, const string& title) {
	_width = width;
	_height = height;
	_title = title;
}

void MainWindow::render() {
	_window.create(VideoMode(_width, _height), _title, Style::Close);

	loadMap();

	_player = Player(Vector2f(1200, 100));

	time_point<system_clock> timePoint = system_clock::now();

	while (_window.isOpen()) {
		if ((system_clock::now().time_since_epoch() - timePoint.time_since_epoch()) >=
			chrono::milliseconds(TIME_PER_FRAME)) {

			dispatchEvents();

			checkForKeyboardKeyPressed();

			_player.applyMove();

			detectCollisions();

			displayFrame();

			timePoint = system_clock::now();
		}

	}
}

void MainWindow::dispatchEvents() {
	Event e;

	while (_window.pollEvent(e)) {
		switch (e.type) {
		case Event::Closed:
			close();
			break;
		}
	}
}

void MainWindow::displayFrame() {
	_window.clear(WINDOW_BACK_COLOR);

	// display world
	for (WorldBloc& bloc : _world) {
		_window.draw(bloc.getVertexRef());
	}

	_player.draw(_window);

	_window.display();
}

void MainWindow::close() {
	_window.close();
}

void MainWindow::loadMap() {
	Image map;
	map.loadFromFile(MAP_FILE_LOCATION);

	for (int x = 0; x < 80; ++x) {
		float posX = x * WORLD_BLOC_SIZE;

		for (int y = 0; y < 40; ++y) {
			Color color = map.getPixel(x, y);

			if (WorldBloc::getType(color) != WorldBlocType::BACKGROUND) {
				Vector2f pos(posX, y * WORLD_BLOC_SIZE);
				Vector2i gridPos(x, y);

				WorldBloc bloc(pos, color, WORLD_BLOC_SIZE, gridPos);

				_world.push_back(bloc);
			}
		}
	}
}

void MainWindow::checkForKeyboardKeyPressed() {
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		_player.rotateLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		_player.rotateRight();
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		_player.moveForward();
	}
	else {
		_player.stopMoveForward();
	}
}

bool MainWindow::playerIntersects(WorldBloc& bloc, Border& return_border) {

	Vector2f bpos = bloc.getPos();
	Vector2f ppos = _player.getPos();

	vector<Border> borders = {
		Border(Vector2f(bpos.x + WORLD_BLOC_SIZE, bpos.y), Direction::TOP),
		Border(Vector2f(bpos.x, bpos.y + WORLD_BLOC_SIZE), Direction::BOTTOM),
		Border(Vector2f(bpos.x, bpos.y), Direction::LEFT),
		Border(Vector2f(bpos.x + WORLD_BLOC_SIZE, bpos.y + WORLD_BLOC_SIZE), Direction::RIGHT)
	};

	for (int i = 0; i < WORLD_BLOC_SIZE; ++i) {
		for (Border& border : borders) {
			border._temp_delta = Utils::getDelta(ppos, border._point);

			if (border._temp_delta < PLAYER_RADIUS) {
				border._collision = true;
				if (border._temp_delta < border._delta) {
					border._delta = border._temp_delta;
				}
			}

			border.nextPoint();
		}
	}

	vector<Border> collisions;

	for (Border& border : borders) {
		if (border._collision)
			collisions.push_back(border);
	}

	if (!collisions.empty()) {
		return_border = *min_element(collisions.begin(), collisions.end(), [](Border& a, Border& b) {return a._delta < b._delta;});

		return true;
	}

	return false;
}

void MainWindow::detectCollisions() {

	FloatRect playerGlobalBounds = _player.getGlobalBounds();
	FloatRect playerLocalBounds = _player.getLocalBounds();

	int counter = 0;

	for (WorldBloc& bloc : _world) {
		if (playerGlobalBounds.intersects(bloc.getBounds())) {
			Border border;

			if (playerIntersects(bloc, border)) {

				float delta = PLAYER_RADIUS - border._delta;

				switch (border._direction) {
				case Direction::TOP:
					_player.moveY((-1.0f) * delta);
					break;
				case Direction::BOTTOM:
					_player.moveY(delta);
					break;
				case Direction::LEFT:
					_player.moveX((-1.0f) * delta);
					break;
				case Direction::RIGHT:
					_player.moveX(delta);
					break;
				}
			}
		}
	}
}