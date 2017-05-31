/*
 * Bullet.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include <Game/src/Items/Bullet.h>
#include <Engine/Include/ResourceManager.h>

Bullet::Bullet(glm::vec2 position, glm::vec2 dir, float damage, float speed) :
		_position(position), _dir(dir), _damage(damage), _speed(speed) {
	// TODO Auto-generated constructor stub

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

bool Bullet::update(std::vector<Velociraptor>& raptors) {
	_position += _dir * _speed;
	return _frameCounter++ >= _lifetime;
}

void Bullet::draw(Engine::SpriteBatch& batcher) {

	glm::vec4 destRect(_position.x, _position.y, 5, 5);
	glm::vec4 uv(0, 0, 1, 1);

	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	batcher.draw(destRect, uv,
			Engine::ResourceManager::getTexture("jimmyJump_pack/PNG/bullet.png").id,
			0, color);
}
