/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>

class Player {
public:
	Player();
	virtual ~Player();

	void setPosition(glm::vec2 newPos) {
		_position = newPos;
	}

	glm::vec2 getPosition() {
		return _position;
	}
private:
	glm::vec2 _position;
};

#endif /* PLAYER_H_ */
