/*
 * Velociraptor.h
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#ifndef VELOCIRAPTOR_H_
#define VELOCIRAPTOR_H_

#include <Engine/Include/SpriteBatch.h>
#include "GameEntity.h"

class GameEntity;

class Velociraptor: public GameEntity {
public:
	Velociraptor();
	virtual ~Velociraptor();

	void render(Engine::SpriteBatch& batcher);

	static const int VELOCIRAPTOR_SIZE = 7;
	static constexpr float SPEED = 1;

	void ai(const Engine::Entity target, Dungeon& map);
};

#endif /* VELOCIRAPTOR_H_ */
