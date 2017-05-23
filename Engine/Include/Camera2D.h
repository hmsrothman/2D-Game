/*
 * Camera2D.h
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#ifndef CAMERA2D_H_
#define CAMERA2D_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

class Camera2D {
public:
	Camera2D();
	virtual ~Camera2D();

	void init(int screenWidth, int screenHeight);

	void update();

	void setPosition(const glm::vec2& newPosition) {
		_position = newPosition;
		_needsMatrixUpdate = true;
	}
	void setScale(float newScale) {
		_scale = newScale;
		_needsMatrixUpdate = true;
	}

	glm::vec2 getPosition() const {
		return _position;
	}

	float getScale() const {
		return _scale;
	}

	glm::mat4 getMatrix() const {
		return _cameraMatrix;
	}

	glm::vec2 convertScreenToWorld(glm::vec2 screen);
private:
	int _screenWidth, _screenHeight;
	bool _needsMatrixUpdate;
	float _scale;
	glm::vec2 _position;
	glm::mat4 _cameraMatrix;
	glm::mat4 _orthoMatrix;
};

} /* namespace Engine */

#endif /* CAMERA2D_H_ */
