/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>
#include <Maze.h>

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

	void collide(const tileID*, int xSize, int ySize);

private:
	glm::vec2 _position;
};

#endif /* PLAYER_H_ */
