/*
 * IButton.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#include "IButton.h"
#include "Util.h"
#include "InputManager.h"
#include "Camera2D.h"
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"

namespace Engine {

IButton::IButton(InputManager* inputManager, Camera2D* camera) :
		_inputManager(inputManager), _camera(camera) {

}

IButton::~IButton() {
}

void IButton::update() {
	glm::vec2 mouseCoords = _inputManager->getMouseCoords();
	mouseCoords = _camera->convertScreenToWorld(mouseCoords);
	if (!overlaps(_rectangle, glm::vec4(mouseCoords.x, mouseCoords.y, 0, 0))) {
		if (_hover) {
			onMouseExit();
			_hover = false;
		}
		if (_click) {
			onRelease();
			_click = false;
		}
	} else {
		if (!_hover) {
			onMouseEnter();
			_hover = true;
		}
		if (_inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
			if (!_click) {
				onPress();
				_click = true;
			}
		} else {
			if (_click) {
				onRelease();
				_click = false;
			}
		}
	}
}

} /* namespace Engine */
