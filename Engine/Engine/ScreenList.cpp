/*
 * ScreenList.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: Simon
 */

#include <IMainGame.h>
#include "ScreenList.h"
#include "IGameScreen.h"

namespace Engine {

ScreenList::ScreenList(IMainGame* game) :
		_parent(game) {
	// TODO Auto-generated constructor stub

}

ScreenList::~ScreenList() {
	destroy();
}

IGameScreen* ScreenList::moveNext() {
	IGameScreen* current = getCurrent();
	if (current->getNextScreenIndex() != NO_SCREEN) {
		_currentScreenIndex = current->getNextScreenIndex();
	}
	return getCurrent();
}

IGameScreen* ScreenList::movePrev() {
	IGameScreen* current = getCurrent();
	if (current->getPrevScreenIndex() != NO_SCREEN) {
		_currentScreenIndex = current->getPrevScreenIndex();
	}
	return getCurrent();
}

IGameScreen* ScreenList::getCurrent() {
	if (_currentScreenIndex == -1) {
		return nullptr;
	}
	return _screens[_currentScreenIndex];
}

void ScreenList::setScreen(int next) {

}
void ScreenList::addScreen(IGameScreen* newScreen) {
	_screens.push_back(newScreen);
	newScreen->build();
	newScreen->setParent(_parent);
}

void ScreenList::destroy() {
	for (int i = 0; i < _screens.size(); i++) {
		_screens[i]->destroy();
		delete _screens[i];
	}
	_screens.resize(0);
	_currentScreenIndex = NO_SCREEN;
}

} /* namespace Engine */

