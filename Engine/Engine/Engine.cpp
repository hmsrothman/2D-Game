/*
 * Engine.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

<<<<<<< HEAD
#include <SDL.h>
#include <Gl\glew.h>
#include <Gl\gl.h>
#include "Errors.h"
=======
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <OpenGL/gl3.h>
#include <iostream>
>>>>>>> refs/remotes/origin/master

namespace Engine {
int init() {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
			SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}
}
