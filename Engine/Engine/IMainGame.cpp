/*
 * IMainGame.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#include "IMainGame.h"
#include "Engine.h"

namespace Engine {

IMainGame::IMainGame() {
	// TODO Auto-generated constructor stub

}

IMainGame::~IMainGame() {
	// TODO Auto-generated destructor stub
}

void IMainGame::run() {
	init();
	gameLoop();
}

void IMainGame::init() {
	Engine::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	_fpsLimiter.setMaxFPS(_maxFPS);

	initShaders();

	onInit();
}

void IMainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
	}
}

void IMainGame::gameLoop() {
	while (_isRunning) {
		_fpsLimiter.begin();
		processInput();
		update();
		draw();
		_window.swapBuffers();
		_fps = _fpsLimiter.end();
	}
}

} /* namespace Engine */
