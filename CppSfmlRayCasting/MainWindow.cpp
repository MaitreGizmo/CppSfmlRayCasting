#include <iostream>
#include <chrono>
#include <cmath>

#include "MainWindow.h"
#include "Settings.h"

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
		case Event::KeyPressed:
			keyPressed(e);
			break;
		case Event::KeyReleased:
			keyReleased(e);
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

void MainWindow::detectCollisions() {
	//FloatRect playerHitbox = _player.getVertexRef().getBounds();

	//const size_t TOP = 0;
	//const size_t BOTTOM = 1;
	//const size_t LEFT = 2;
	//const size_t RIGHT = 3;

	//vector<vector<WorldBloc>> intersections(4, vector<WorldBloc>(0));

	//int intersectionsCount = 0;

	//bool topLeft = false;
	//bool topRight = false;
	//bool bottomLeft = false;
	//bool bottomRight = false;

	//WorldBloc blocTopLeft;
	//WorldBloc blocTopRight;
	//WorldBloc blocBottomLeft;
	//WorldBloc blocBottomRight;

	//for (WorldBloc& bloc : _world) {
	//	if (_player.getVertexRef().getBounds().intersects(bloc.getVertexRef().getBounds())) {

	//		intersectionsCount++;

	//		float px = _player.getPos().x;
	//		float py = _player.getPos().y;

	//		float bx = bloc.getPos().x;
	//		float by = bloc.getPos().y;

	//		FloatRect playerHitBox = _player.getVertexRef().getBounds();
	//		FloatRect blocHitBox = bloc.getVertexRef().getBounds();

	//		if (blocHitBox.contains(Vector2f(px, py))) {
	//			topLeft = true;
	//			blocTopLeft = bloc;
	//			cout << "> blocTopLeft found" << endl;
	//		}

	//		if (blocHitBox.contains(Vector2f(px + PLAYER_SIZE, py))) {
	//			topRight = true;
	//			blocTopRight = bloc;
	//			cout << "> blocTopRight found" << endl;
	//		}

	//		if (blocHitBox.contains(Vector2f(px, py + PLAYER_SIZE))) {
	//			bottomLeft = true;
	//			blocBottomLeft = bloc;
	//			cout << "> blocBottomLeft found" << endl;
	//		}

	//		if (blocHitBox.contains(Vector2f(px + PLAYER_SIZE, py + PLAYER_SIZE))) {
	//			bottomRight = true;
	//			blocBottomRight = bloc;
	//			cout << "> blocBottomRight found" << endl;
	//		}
	//	}
	//}

	//if (intersectionsCount > 0) {
	//	cout << "> intersections count : " << intersectionsCount << endl;

	//	float mx = _player.getMove().x;
	//	float my = _player.getMove().y;

	//	// player go left
	//	if (mx < 0.0f && (topLeft || bottomLeft)) {

	//		// player go top
	//		if (my < 0.0f) {
	//			// => top / left
	//			correctCollisionTop(blocTopLeft);
	//			correctCollisionLeft(blocTopLeft);

	//			return;
	//		}

	//		// player go bottom
	//		if (my > 0.0f) {
	//			// => bottom / left
	//			correctCollisionBottom(blocBottomLeft);
	//			correctCollisionLeft(blocBottomLeft);

	//			return;
	//		}

	//		// player don't move on Y axis
	//		if (my == 0.0f) {
	//			// => left
	//			correctCollisionLeft(blocTopLeft);
	//			correctCollisionLeft(blocBottomLeft);

	//			return;
	//		}

	//	}

	//	// player go right
	//	if (mx > 0.0f && (topRight || bottomRight)) {

	//		// player go top
	//		if (my < 0.0f) {
	//			// => top / right
	//			correctCollisionTop(blocTopRight);
	//			correctCollisionRight(blocTopRight);

	//			return;
	//		}

	//		// player go bottom
	//		if (my > 0.0f) {
	//			// => bottom / right
	//			correctCollisionBottom(blocBottomRight);
	//			correctCollisionRight(blocBottomRight);

	//			return;
	//		}

	//		// player don't move on Y axis
	//		if (my == 0.0f) {
	//			// => right
	//			correctCollisionRight(blocBottomRight);
	//			correctCollisionRight(blocTopRight);

	//			return;
	//		}

	//	}

	//	// player don't move on X axis
	//	if (mx == 0.0f) {

	//		// player go top
	//		if (my < 0.0f) {
	//			// => top
	//			correctCollisionTop(blocTopLeft);
	//			correctCollisionTop(blocTopRight);

	//			return;
	//		}

	//		// player go bottom
	//		if (my > 0.0f) {
	//			// => bottom
	//			correctCollisionBottom(blocBottomLeft);
	//			correctCollisionBottom(blocBottomRight);

	//			return;
	//		}

	//		// player don't move on Y axis
	//		if (my == 0.0f) {
	//			// => static
	//			correctCollisionLeft(blocTopLeft);
	//			correctCollisionLeft(blocBottomLeft);

	//			correctCollisionRight(blocTopRight);
	//			correctCollisionRight(blocBottomRight);

	//			correctCollisionTop(blocTopLeft);
	//			correctCollisionTop(blocTopRight);

	//			correctCollisionBottom(blocBottomLeft);
	//			correctCollisionBottom(blocBottomRight);

	//			return;
	//		}

	//	}
	//}
}

void MainWindow::keyPressed(Event e) {
	switch (e.key.code) {
	case Keyboard::Left:

		break;
	case Keyboard::Right:

		break;
	case Keyboard::Up:

		break;
	case Keyboard::Down:

		break;
	}
}

void MainWindow::keyReleased(Event e) {
	switch (e.key.code) {
	case Keyboard::Left:

		break;
	case Keyboard::Right:

		break;
	case Keyboard::Up:

		break;
	case Keyboard::Down:

		break;
	}
}

void MainWindow::correctCollisionTop(WorldBloc& bloc) {
	/*if (_player.getVertexRef().getBounds().intersects(bloc.getVertexRef().getBounds())) {
		float py = _player.getPos().y;
		float by = bloc.getPos().y;

		float delta = (by + WORLD_BLOC_SIZE) - py;
		_player.setPosY(py + delta);
	}*/
}

void MainWindow::correctCollisionBottom(WorldBloc& bloc) {
	/*if (_player.getVertexRef().getBounds().intersects(bloc.getVertexRef().getBounds())) {
		float py = _player.getPos().y;
		float by = bloc.getPos().y;

		float delta = (py + PLAYER_SIZE) - by;
		_player.setPosY(py - delta);
	}*/
}

void MainWindow::correctCollisionLeft(WorldBloc& bloc) {
	/*if (_player.getVertexRef().getBounds().intersects(bloc.getVertexRef().getBounds())) {
		float px = _player.getPos().x;
		float bx = bloc.getPos().x;

		float delta = (bx + WORLD_BLOC_SIZE) - px;
		_player.setPosX(px + delta);
	}*/
}

void MainWindow::correctCollisionRight(WorldBloc& bloc) {
	/*if (_player.getVertexRef().getBounds().intersects(bloc.getVertexRef().getBounds())) {
		float px = _player.getPos().x;
		float bx = bloc.getPos().x;

		float delta = (px + PLAYER_SIZE) - bx;
		_player.setPosX(px - delta);
	}*/
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