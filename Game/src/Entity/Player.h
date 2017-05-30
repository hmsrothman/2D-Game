/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>
#include "GameEntity.h"
#include "../Dungeon/Dungeon.h"

class Player: public GameEntity {
public:
	Player();
	virtual ~Player();

	const static int PLAYER_SIZE = 10;

	void render(Engine::SpriteBatch& batcher) const; // this appears to not work

	void move(glm::vec2 displacement, Dungeon& map);

	void kill();

	bool isded=false;
private:
};

#endif /* PLAYER_H_ */
