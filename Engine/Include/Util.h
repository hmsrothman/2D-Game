/*
 * Util.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#ifndef UTIL_H_
#define UTIL_H_

namespace Engine {

bool overlaps(const glm::vec4& self, const glm::vec4& other) {
	glm::ivec2 l1(self.x, self.y);
	glm::ivec2 r1(self.x + self.z, self.y + self.w);

	glm::ivec2 l2(other.x, other.y);
	glm::ivec2 r2(other.x + other.z, other.y + other.w);

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

}

#endif /* UTIL_H_ */
