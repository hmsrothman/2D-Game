/*
 * InputManager.h
 *
 *  Created on: May 21, 2017
 *      Author: Simon
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include<unordered_map>

namespace Engine {

class InputManager {
public:
	InputManager();
	virtual ~InputManager();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
private:
	std::unordered_map<unsigned int, bool> _keyMap;
};

} /* namespace Engine */

#endif /* INPUTMANAGER_H_ */
