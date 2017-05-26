/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>
#include "Dungeon.h"

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

	void move(glm::vec2 translation,  Dungeon& map);


	void render(Engine::SpriteBatch batcher); // this appears to not work

private:
	glm::vec2 _position;
};

#endif /* PLAYER_H_ */
