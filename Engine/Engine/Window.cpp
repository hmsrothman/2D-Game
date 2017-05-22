/*
 * Window.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include "Window.h"
#include "Errors.h"
namespace Engine {

Window::Window() {
	// TODO Auto-generated constructor stub

}

Window::~Window() {
	// TODO Auto-generated destructor stub
}

int Window::create(std::string windowName, int width, int height,
		unsigned int currentFlags) {
	unsigned int flags = SDL_WINDOW_OPENGL;
	if (currentFlags & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (!_SDLWindow) {
		fatalError("SDL Window Creation Failed!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_SDLWindow);
	if (!glContext) {
		fatalError(SDL_GetError());
	}

	glClearColor(0.0, 0, 0.0, 1.0);

	SDL_GL_SetSwapInterval(0); //turn on vsync

	return 0;
}

void Window::swapBuffers() {
	SDL_GL_SwapWindow(_SDLWindow);
}

}
