/*
 * PoissonGenerator.h
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#ifndef POISSONGENERATOR_H_
#define POISSONGENERATOR_H_

#include <vector>
#include <glm/glm.hpp>

class PoissonGenerator {
public:
	PoissonGenerator();
	virtual ~PoissonGenerator();

	std::vector<glm::ivec2> pts;

	void generate(int pointsPerIter, int width, int numPoints);
private:
	int _pointsPerIter, _width, _remainingPoints;

	void iterate();
	float minDist(glm::ivec2 point); //minimum distance from all other points that have been selected so far
};

#endif /* POISSONGENERATOR_H_ */
