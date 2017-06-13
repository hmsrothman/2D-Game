/*
 * errors.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#else
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#endif
#include "Errors.h"
namespace Engine{

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	SDL_Quit();
	exit(1);
}
}
