/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "dungeon.h"

#include <glm/glm.hpp>


class Player {
public:
	Player();
	virtual ~Player();

	const static int PLAYER_SIZE = 15;

	void setPosition(glm::vec2 newPos) {
		_position = newPos;
	}

	glm::vec2 getPosition() {
		return _position;
	}

	void move(glm::vec2 translation, const Dungeon& map) {
		//make a Rectangle which is player sprite
		//use Rectangle and some Rectangles representing map tiles to check which tiles player is on
		//make Rectangle(s) which is the wall portion(s) of map tile(s) the player is on
		//if the player overlaps this (these) rectangle(s), correct accordingly
		//this will work IFF player speed << path width
		//if player speed !<< path width gameplay would be fucked anyway so i think we're good

	}

private:
	glm::vec2 _position;
};

#endif /* PLAYER_H_ */
