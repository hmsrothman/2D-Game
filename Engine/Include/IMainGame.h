/*
 * IMainGame.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#ifndef IMAINGAME_H_
#define IMAINGAME_H_

#include "Window.h"
#include "Timing.h"
#include "InputManager.h"

namespace Engine {

class IMainGame {
public:
	IMainGame();
	virtual ~IMainGame();

	void run();
private:
	Window _window;

	FPSLimiter _fpsLimiter;

	bool _isRunning = true;

	void init();
	void processInput();
	void gameLoop();
protected:
	int _screenWidth = 1024;
	int _screenHeight = 768;

	float _maxFPS = 60;
	float _fps = 0;

	InputManager _inputManager;

	virtual void initShaders() = 0;
	virtual void onInit()=0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

} /* namespace Engine */

#endif /* IMAINGAME_H_ */
