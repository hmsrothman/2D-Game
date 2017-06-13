/*
 * Timing.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef TIMING_H_
#define TIMING_H_

namespace Engine {

class FPSLimiter {
public:
	FPSLimiter();
	~FPSLimiter();

	void init(float fps);

	void setMaxFPS(float fps);

	void begin();
	float end(); //returns fps

private:
	float _maxFPS = 0;
	unsigned int _startTicks = 0;
	unsigned int _endTicks = 0;
	float _fps = 0;
	float _frameTime = 0;

	void calculateFPS();
};

}

#endif /* TIMING_H_ */
