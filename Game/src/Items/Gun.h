/*
 * Gun.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef GUN_H_
#define GUN_H_
#include <glm/glm.hpp>
#include "Bullet.h"
#include <string>

class Gun {
public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float _spread,
			float speed, float damage, int clip);
	virtual ~Gun();
	int ammo = 10;
	int damage = 5;
	int fireDelay = 1;
	void update(bool isMouseDown, const glm::vec2& pos, const glm::vec2& dir,
			std::vector<Bullet>& bullets);
	void addAmmo(int amount);
private:
	std::string _name;

	int _fireRate; //in frames
	int _bulletsPerShot; //bullets fired at a time
	float _spread; //accuracy

	float _bulletSpeed;
	float _bulletDamage;

	int _frameCounter = 0;

	int _clip;

	void fire(const glm::vec2& pos, const glm::vec2& dir,
			std::vector<Bullet>& bullets);
};

#endif /* GUN_H_ */
