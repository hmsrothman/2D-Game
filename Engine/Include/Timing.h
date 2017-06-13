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
	float _maxFPS;
	unsigned int _startTicks;
	unsigned int _endTicks;
	float _fps;
	float _frameTime;

	void calculateFPS();
};

}

#endif /* TIMING_H_ */
