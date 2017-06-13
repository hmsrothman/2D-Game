/*
 * Bullet.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <glm/glm.hpp>
#include <Engine/Include/SpriteBatch.h>
#include "../Rectangle.h"

class Velociraptor;
class Dungeon;

class Bullet {
public:
	Bullet(glm::vec2 position, glm::vec2 dir, float damage, float speed);
	virtual ~Bullet();

	int renderSize = 5;

	bool update(Dungeon& map, std::vector<Velociraptor>& raptors);
	void draw(Engine::SpriteBatch& batcher);
	Rectangle getBoundingBox();

	bool shouldDie = false;
	float damage;

private:
	glm::vec2 _position;
	glm::vec2 _dir;
	float _speed;

	int _lifetime = 60; //in frames
	int _frameCounter = 0;

};

#endif /* BULLET_H_ */
