/*
 * InputManager.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Simon
 */

#include <InputManager.h>

namespace Engine {

InputManager::InputManager() {
	// TODO Auto-generated constructor stub

}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}

void InputManager::pressKey(unsigned int keyID) {
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		return it->second;
	} else {
		return false;
	}
}

} /* namespace Engine */
