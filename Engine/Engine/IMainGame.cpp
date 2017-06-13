/*
 * MainGame.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: Simon
 */

#include <IMainGame.h>
#include "Engine.h"
#include "Timing.h"
#include "ScreenList.h"
#include "IGameScreen.h"

namespace Engine {

IMainGame::IMainGame() {
	// TODO Auto-generated constructor stub

}

IMainGame::~IMainGame() {
	// TODO Auto-generated destructor stub
}

void IMainGame::run() {
	if (!init()) {
		return;
	}
	FPSLimiter limiter;
	limiter.setMaxFPS(60);

	_isRunning = true;

	while (_isRunning) {
		limiter.begin();
		update();
		draw();

		_fps = limiter.end();
	}
}

void IMainGame::exit() {
	if (_screenList) {
		_screenList->getCurrent()->exit();
		_screenList->destroy();
		_screenList.reset();
	}
	_isRunning = false;
}

bool IMainGame::init() {
	Engine::init();
	initSystems();
	onInit();
	addScreens();
	_currentScreen = _screenList->getCurrent();
	_currentScreen->enter();
	return true;
}

bool IMainGame::initSystems() {
	_window.create("Default", 1920, 1080, 0);
}

void IMainGame::update() {
	if(_currentScreen){
		switch(_currentScreen->getState())
	}
}

void IMainGame::draw() {

}

} /* namespace Engine */
