/*
 * MainGame.h
 *
 *  Created on: Jun 8, 2017
 *      Author: Simon
 */

#ifndef IMAINGAME_H_
#define IMAINGAME_H_
#include <memory>
#include "Window.h"

namespace Engine {

class ScreenList;
class IGameScreen;

class IMainGame {
public:
	IMainGame();

	virtual ~IMainGame();

	void run();
	void exit();

	virtual void onInit() = 0;
	virtual void addScreens() = 0; //setup all the screens
	virtual void onExit() = 0;

	const float getFps() const {
		return _fps;
	}
protected:
	std::unique_ptr<ScreenList> _screenList = nullptr;
	IGameScreen* _currentScreen = nullptr;
	bool _isRunning = false;
	float _fps = 0;
	Window _window;

	bool init();
	bool initSystems();

	void update();
	void draw();
};

} /* namespace Engine */

#endif /* IMAINGAME_H_ */
