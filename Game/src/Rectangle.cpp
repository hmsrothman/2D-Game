/*
 * Rectangle.cpp
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#include <Game/src/Rectangle.h>
#include <iostream>

Rectangle::Rectangle(int x, int y, int xSize, int ySize) :
		position(x, y, xSize, ySize) {

}

Rectangle::~Rectangle() {
}

bool Rectangle::overlaps(const Rectangle& other) const {

	glm::ivec2 l1(position.x, position.y);
	glm::ivec2 r1(position.x + position.z, position.y + position.w);

	glm::ivec2 l2(other.position.x, other.position.y);
	glm::ivec2 r2(other.position.x + other.position.z,
			other.position.y + other.position.w);

	// If one rectangle is on left side of other
	if (r1.y < l2.y || l1.y > r2.y) {
		return false;
	}

	// If one rectangle is above other
	if (r1.x < l2.x || l1.x > r2.x) {
		return false;
	}

	return true;
}
