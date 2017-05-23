/*
 * Player.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include <Game/src/Player.h>

Player::Player() :
		_position(0, 0) {
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::collide(const tileID*, int xSize, int ySize) {
	std::vector<glm::ivec2> collideTiles;
	glm::ivec2 cornerPos1 = glm::ivec2(_position);
}
}
