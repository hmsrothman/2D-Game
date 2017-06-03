//============================================================================
// Name        : GraphicsEngine.cpp
// Author      : Simon Rothman
// Version     :
// Copyright   : 
//============================================================================

#include <iostream>
#include "MainGame.h"
#include <cstdlib>
#include <time.h>

using namespace std;

/*
 * This is the main function; there's probably not reason to do anything here
 * all it does is call game.run
 */

int main(int arc, char** argv) {
	std::srand(time(0));
	MainGame game;
	game.run();
	return 0;
}
