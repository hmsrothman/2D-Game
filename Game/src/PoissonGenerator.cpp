/*
 * PoissonGenerator.cpp
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#include <Game/src/PoissonGenerator.h>
#include <cstdlib>

PoissonGenerator::PoissonGenerator() :
		_width(0), _pointsPerIter(0), _remainingPoints(0) {
	// TODO Auto-generated constructor stub

}

PoissonGenerator::~PoissonGenerator() {
	// TODO Auto-generated destructor stub
}

void PoissonGenerator::generate(int pointsPerIter, int width, int numPoints) {
	pts.clear();

	_pointsPerIter = pointsPerIter;
	_width = width;
	_remainingPoints = numPoints;

	while (_remainingPoints > 0) {
		iterate();
		--_remainingPoints;
	}
}

void PoissonGenerator::iterate() {
	std::vector<glm::ivec2> possiblePoints(_pointsPerIter);
	for (int i = 0; i < _pointsPerIter; i++) { //gen some points
		int x = std::rand() % _width;
		int y = std::rand() % _width;

		possiblePoints.emplace_back(x, y);
	}

	//chose the best one
	glm::ivec2 bestPoint;
	float maxDist = 0;

	for (int i = 0; i < possiblePoints.size(); i++) {
		float distance = minDist(possiblePoints[i]);
		if (distance > maxDist) {
			maxDist = distance;
			bestPoint = possiblePoints[i];
		}
	}

	pts.push_back(bestPoint);
}

float PoissonGenerator::minDist(glm::ivec2 point) {
	float minDist = 2 << 10; //or something
	for (int i = 0; i < pts.size(); i++) {
		float dist = glm::length(glm::vec2(pts[i]) - glm::vec2(point));
		if (dist < minDist) {
			minDist = dist;
		}
	}
	return minDist;
}
