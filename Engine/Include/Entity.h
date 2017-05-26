/*
 * Entity.h
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <glm/glm.hpp>

namespace Engine {

class Entity {
public:
	Entity() :
			_position(0, 0) {

	}
	glm::vec2 getPosition() const {
		return _position;
	}
protected:
	glm::vec2 _position;
};

}
#endif /* ENTITY_H_ */
