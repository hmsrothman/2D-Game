/*
 * Camera2D.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include <Camera2D.h>

namespace Engine {

Camera2D::Camera2D() :
		_position(0, 0), _scale(1),  _cameraMatrix(1), _needsMatrixUpdate(true), _screenWidth(
				500), _screenHeight(500), _orthoMatrix(1),  _focus(
				nullptr), _locked(0){

}

Camera2D::~Camera2D() {

}

void Camera2D::update() {
	if (!_locked) {
		if (_needsMatrixUpdate) {
			glm::vec3 translate(-_position.x, -_position.y, 0);

			glm::vec3 scale(_scale, _scale, 0);
			_orthoMatrix = glm::ortho((float) (-_screenWidth / 2.0 * scale.x),
					(float) (_screenWidth / 2.0 * scale.x),
					(float) (-_screenHeight / 2.0 * scale.y),
					(float) (_screenHeight / 2.0 * scale.y));
			_cameraMatrix = glm::translate(_orthoMatrix, translate); //TRANSLATE

			_needsMatrixUpdate = false;
		}
	} else {
		_position = _focus->getPosition();
		glm::vec3 translate(-_position.x, -_position.y, 0);

		glm::vec3 scale(_scale, _scale, 0);
		_orthoMatrix = glm::ortho((float) (-_screenWidth / 2.0 * scale.x),
				(float) (_screenWidth / 2.0 * scale.x),
				(float) (-_screenHeight / 2.0 * scale.y),
				(float) (_screenHeight / 2.0 * scale.y));
		_cameraMatrix = glm::translate(_orthoMatrix, translate); //TRANSLATE

		_needsMatrixUpdate = false;
	}
}

void Camera2D::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float) _screenWidth, 0.0f,
			(float) _screenHeight);
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screen) {
	screen.x -= _screenWidth / 2;
	screen.y -= _screenHeight / 2;
	screen.x /= _screenWidth / 2;
	screen.y /= -_screenHeight / 2;
	glm::vec4 coords(screen.x, screen.y, 0, 1);
	coords = coords * glm::inverse(_cameraMatrix);
	coords += glm::vec4(_position, 0, 0);
	return glm::vec2(coords.x, coords.y);
}

void Camera2D::lockToEntity(Entity *entity) {
	_locked = true;
	_focus = entity;
}

} /* namespace Engine */
