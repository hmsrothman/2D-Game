/*
 * Timing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include <Timing.h>
#ifdef _WIN32
#include <SDL.h>
#else
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#endif

namespace Engine {

FPSLimiter::FPSLimiter() {

}

FPSLimiter::~FPSLimiter() {

}

void FPSLimiter::init(float fps) {
	setMaxFPS(fps);

}

void FPSLimiter::setMaxFPS(float fps) {
	_maxFPS = fps;
}

void FPSLimiter::begin() {
	_startTicks = SDL_GetTicks();
}

float FPSLimiter::end() {
	//limit fps to max; redundant with vsync which should be on, but whatever
	float frameTicks = SDL_GetTicks() - _startTicks;

	if (1000 / _maxFPS > frameTicks) {
		SDL_Delay(1000 / _maxFPS - frameTicks);
	}

	calculateFPS();

	return _fps;
}

void FPSLimiter::calculateFPS() {
	static const int NUM_SAMPLES = 100;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	previousTicks = currentTicks;

	int count = ++currentFrame < NUM_SAMPLES ? currentFrame : NUM_SAMPLES;
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 60;
	}

	float frameTicks = SDL_GetTicks() - _startTicks;

	if (1000 / _maxFPS > frameTicks) {
		SDL_Delay(1000 / _maxFPS - frameTicks);
	}
}

}
