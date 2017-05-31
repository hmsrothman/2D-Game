/*
 * Gun.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include <Game/src/Items/Gun.h>
#include <iostream>
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread,
		float speed, float damage) :
		_name(name), _fireRate(fireRate), _bulletsPerShot(bulletsPerShot), _spread(
				spread), _bulletSpeed(speed), _bulletDamage(damage) {
}

Gun::~Gun() {
}

void Gun::update(bool isMouseDown, const glm::vec2& pos, const glm::vec2& dir,
		std::vector<Bullet>& bullets) {
	_frameCounter++;
	if (_frameCounter > _fireRate && isMouseDown) {
		fire(pos, dir, bullets);
		_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2& pos, const glm::vec2& dir,
		std::vector<Bullet>& bullets) {

	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randRotate(-_spread, _spread);
	for (int i = 0; i < _bulletsPerShot; i++) {
		bullets.emplace_back(pos, glm::rotate(dir, randRotate(randomEngine)),
				_bulletDamage, _bulletSpeed);
	}
}

