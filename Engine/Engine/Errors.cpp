/*
 * errors.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include <iostream>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "Errors.h"
namespace Engine{

void fatalError(const std::string& errorString) {
	std::cout << errorString << std::endl;
	SDL_Quit();
	exit(1);
}
}
