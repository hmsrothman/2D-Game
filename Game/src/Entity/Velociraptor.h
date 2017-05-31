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
	~Velociraptor();

	void render(Engine::SpriteBatch& batcher) const;

	static const int VELOCIRAPTOR_SIZE = 10;
	static constexpr float SPEED = 1;

<<<<<<< HEAD:Game/src/Velociraptor.h
	void ai(const Engine::Entity target, Dungeon map);
=======
	void ai(GameEntity& target, Dungeon& map);

	void kill();

	glm::ivec2 currentDir;
>>>>>>> refs/remotes/origin/master:Game/src/Entity/Velociraptor.h
};

#endif /* VELOCIRAPTOR_H_ */
