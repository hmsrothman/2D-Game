/*
 * Bullet.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include <Game/src/Items/Bullet.h>
#include <Engine/Include/ResourceManager.h>
#include "../Dungeon/TileFlags.h"
#include "../Dungeon/Dungeon.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 dir, float Damage, float speed) :
		_position(position), _dir(dir), damage(Damage), _speed(speed) {

}

Bullet::~Bullet() {
}

bool Bullet::update(Dungeon& map, std::vector<Velociraptor>& raptors) {
	_position += _dir * _speed;

	if (_frameCounter++ >= _lifetime) {
		return true;
	}
	if (!(map.tileArray[map.getIndex(_position.x / map.scale,
			_position.y / map.scale)] & NAVIGABLE)) {
		return true;
	}
	return shouldDie;
}

void Bullet::draw(Engine::SpriteBatch& batcher) {

	glm::vec4 destRect(_position.x, _position.y, renderSize, renderSize);
	glm::vec4 uv(0, 0, 1, 1);

	Engine::Color color(255,255,255,255);

	batcher.draw(destRect, uv,
			Engine::ResourceManager::getTexture("jimmyJump_pack/PNG/bullet.png").id,
			0, color);
}

Rectangle Bullet::getBoundingBox() {
	return Rectangle(_position.x, _position.y, renderSize, renderSize);
}
