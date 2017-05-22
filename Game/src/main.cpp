//============================================================================
// Name        : GraphicsEngine.cpp
// Author      : Simon Rothman
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MainGame.h"
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int arc, char** argv) {
	std::srand(time(0));
	MainGame game;
	game.run();
	return 0;
}
