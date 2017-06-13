/*
 * IButton.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#ifndef IBUTTON_H_
#define IBUTTON_H_

#include "GLTexture.h"
#include <glm/glm.hpp>

namespace Engine {

class InputManager;
class Camera2D;

class IButton {
public:
	IButton(InputManager* inputManager, Camera2D* camera);
	virtual ~IButton();

	virtual void onPress() = 0;
	virtual void onRelease() = 0;

	virtual void onMouseEnter() = 0;
	virtual void onMouseExit() = 0;

	void update();
protected:
	bool _hover = false;
	bool _click = false;

	InputManager* _inputManager = nullptr;
	Camera2D* _camera = nullptr;

	glm::vec4 _rectangle; //vec4(x.y.xsize,ysize)
};

} /* namespace Engine */

#endif /* IBUTTON_H_ */
