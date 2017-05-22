/*
 * Window.h
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <OpenGL/gl3.h>
#include <string>
namespace Engine {

enum windowFlags {
	INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4
};

class Window {
public:
	Window();
	virtual ~Window();

	int create(std::string windowName, int width, int height,
			unsigned int currentFlags);

	int getScreenWidth() {
		return _screenWidth;
	}

	int getScreenHeight() {
		return _screenHeight;
	}

	void swapBuffers();

private:
	SDL_Window* _SDLWindow;
	int _screenWidth, _screenHeight;
};
}
#endif /* WINDOW_H_ */
