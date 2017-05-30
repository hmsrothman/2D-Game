/*
 * GameEntity.h
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <Engine/Include/Entity.h>
#include <glm/glm.hpp>
#include "Dungeon.h"

class Dungeon;

class GameEntity: public Engine::Entity {
public:
	GameEntity(int size) :
			renderSize(size) {
	}
	virtual ~GameEntity() {

	}
	void setPosition(glm::vec2 newPos) {
		_position = newPos;
	}
	int renderSize;
	void move(glm::vec2 translation, Dungeon& map);
	virtual void render(Engine::SpriteBatch& batcher) const = 0;

	virtual void kill()=0;

	const static glm::ivec2 UP, DOWN, LEFT, RIGHT;
};

#endif /* GAMEENTITY_H_ */
