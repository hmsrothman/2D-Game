/*
 * Rectangle.h
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <glm/glm.hpp>

class Rectangle {
public:
	Rectangle(int x, int y, int xSize, int ySize);
	virtual ~Rectangle();

	glm::ivec4 position; //x, y, xSize, ySize

	bool overlaps(const Rectangle& other) const;
};

#endif /* RECTANGLE_H_ */
