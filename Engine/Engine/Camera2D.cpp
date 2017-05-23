/*
 * Camera2D.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include <Camera2D.h>

namespace Engine {

Camera2D::Camera2D() :
		_position(0, 0), _cameraMatrix(1), _scale(1), _needsMatrixUpdate(true), _screenWidth(
				500), _screenHeight(500), _orthoMatrix(1) {

}

Camera2D::~Camera2D() {

}

void Camera2D::update() {
	if (_needsMatrixUpdate) {
		glm::vec3 translate(-_position.x + _screenWidth / 2,
				-_position.y + _screenHeight / 2, 0);

		glm::vec3 scale(_scale, _scale, 0);
		_cameraMatrix = glm::scale(_orthoMatrix, scale); //SCALE
		_cameraMatrix = glm::translate(_cameraMatrix, translate); //TRANSLATE

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
	screen.y = _screenHeight - screen.y;
	screen -= glm::vec2(_screenWidth / 2, _screenHeight / 2); 	//center 0,0
	screen /= _scale; 											//scale
	screen += _position;										//translate;
	return screen;
}

} /* namespace Engine */
