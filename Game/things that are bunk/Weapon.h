/*
 * Weapon.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include <Game/src/Items/Item.h>
#include <glm/glm.hpp>
#include "../Entity/GameEntity.h"

class Weapon: public Item {
public:
	Weapon();
	virtual ~Weapon();
	virtual void attack(const glm::vec2& dir, const glm::vec2& position)=0;
};

#endif /* WEAPON_H_ */
