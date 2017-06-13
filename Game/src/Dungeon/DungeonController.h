/*
 * DungeonController.h
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#ifndef DUNGEON_DUNGEONCONTROLLER_H_
#define DUNGEON_DUNGEONCONTROLLER_H_

#include "../Entity/Player.h"
#include "Dungeon.h"
#include "../Entity/Velociraptor.h"
#include <Engine/Include/InputManager.h>
#include <Engine/Include/Camera2D.h>

class DungeonController {
public:
	DungeonController();
	virtual ~DungeonController();

	void update(std::vector<Velociraptor>& raptors, GameEntity& target,
			Dungeon& map);
};

#endif /* DUNGEON_DUNGEONCONTROLLER_H_ */
