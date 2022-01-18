#include <cmath>
#include <iostream>

#include "Player.h"
#include "Settings.h"
#include "Utils.h"

using namespace std;
using namespace gst;
using namespace sf;

Player::Player() = default;

Player::Player(Vector2f initPos) {
	_position = initPos;

	float radius = PLAYER_SIZE / 2.0f;

	_shape = CircleShape(radius);
	_shape.setFillColor(Color::Red);
	_shape.setOrigin(Vector2f(radius, radius));
	_shape.setRotation(_rotation);
	_shape.setPosition(_position);

	_line = RectangleShape(Vector2f(radius, 2));
	_line.setFillColor(Color::White);
	_line.setOrigin(Vector2f(0.0f, 1.0f));
	_line.setRotation(_rotation);
	_line.setPosition(_position);
}

void Player::draw(RenderWindow & window) {
	_shape.setPosition(_position);
	_shape.setRotation(Utils::radToDeg(_rotation));

	_line.setPosition(_position);
	_line.setRotation(Utils::radToDeg(_rotation));

	window.draw(_shape);
	window.draw(_line);
}

void Player::applyMove() {
	float moveX = _speed * cos(_rotation);
	float moveY = _speed * sin(_rotation);

	_position += Vector2f(moveX, moveY);
}

void Player::rotateLeft() {
	_rotation -= Utils::degToRad(ROTATION_SPEED);

	correctRotationMultiples();
}

void Player::rotateRight() {
	_rotation += Utils::degToRad(ROTATION_SPEED);

	correctRotationMultiples();
}

void Player::correctRotationMultiples() {
	float rad360deg = Utils::degToRad(360.0f);

	if (_rotation > rad360deg) {
		int mult = int(_rotation) % int(rad360deg);

		_rotation -= float(mult) * rad360deg;
	}
	else if (_rotation < (-1.0f) * rad360deg) {
		int mult = abs(int(_rotation)) % abs(int(rad360deg));

		_rotation += float(mult) * rad360deg;
	}
}

void Player::moveForward() {
	_speed = PLAYER_SPEED;
}

void Player::stopMoveForward() {
	_speed = 0.0f;
}
