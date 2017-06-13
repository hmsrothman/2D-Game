/*
 * IGameScreen.h
 *
 *  Created on: Jun 8, 2017
 *      Author: Simon
 */

#ifndef IGAMESCREEN_H_
#define IGAMESCREEN_H_

namespace Engine {

class IMainGame;

enum class ScreenState {
	NONE, RUNNING, EXIT_APP, CHANGE_NEXT, CHANGE_PREV
};

class IGameScreen {
public:
	IGameScreen() {

	}

	virtual ~IGameScreen() {

	}

	virtual int getNextScreenIndex() const = 0;
	virtual int getPrevScreenIndex() const = 0;

	virtual void build() = 0; //allocates
	virtual void destroy() = 0; //deallocates

	virtual void enter() = 0; //enters screen
	virtual void exit() = 0; //leave screen

	virtual void update() = 0; //update
	virtual void draw() = 0; //draws

	int getIndex() const {
		return _index;
	}

	void setParent(IMainGame* parent) {
		_parent = parent;
	}
protected:
	int _index = -1;

	ScreenState _state = ScreenState::NONE;

	IMainGame* _parent = nullptr;
};

} /* namespace Engine */

#endif /* IGAMESCREEN_H_ */
