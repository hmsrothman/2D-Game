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
#include "GameEntity.h"

class Player: public GameEntity {
public:
	Player();
	virtual ~Player();

	const static int PLAYER_SIZE = 10;

	void setPosition(glm::vec2 newPos) {
		_position = newPos;
	}
	void render(Engine::SpriteBatch& batcher); // this appears to not work

	void move(glm::vec2 displacement, Dungeon& map);

private:
};

#endif /* PLAYER_H_ */
