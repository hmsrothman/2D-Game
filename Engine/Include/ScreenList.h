/*
 * ScreenList.h
 *
 *  Created on: Jun 8, 2017
 *      Author: Simon
 */

#ifndef SCREENLIST_H_
#define SCREENLIST_H_
#include <vector>

#define NO_SCREEN -1

namespace Engine {

class IMainGame;
class IGameScreen;

class ScreenList {
public:
	ScreenList(IMainGame* game);
	virtual ~ScreenList();

	IGameScreen* moveNext();
	IGameScreen* movePrev();
	IGameScreen* getCurrent();

	void setScreen(int next);
	void addScreen(IGameScreen* newScreen);

	void destroy();
protected:
	std::vector<IGameScreen*> _screens;
	int _currentScreenIndex = NO_SCREEN;
	IMainGame* _parent = nullptr;
};

} /* namespace Engine */

#endif /* SCREENLIST_H_ */
