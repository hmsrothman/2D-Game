/*
 * errors.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include <iostream>
#include <SDL.h>
#include "Errors.h"
namespace Engine{

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	SDL_Quit();
	exit(1);
}
}
