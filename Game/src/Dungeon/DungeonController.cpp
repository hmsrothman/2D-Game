/*
 * DungeonController.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include "DungeonController.h"
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <iostream>

DungeonController::DungeonController() {

}

DungeonController::~DungeonController() {
}

void DungeonController::update(std::vector<Velociraptor>& raptors,
		GameEntity& target, Dungeon& map) {
	for (auto& raptor : raptors) {
		raptor.ai(target, map);
		if (raptor.getBoundingBox().overlaps(target.getBoundingBox())) {
			if (!target.invuln) {
				target.health -= raptor.damage;
				target.giveInvulnFrames(59);
			}
		}
	}

	if (target.health <= 0) {
		target.kill();
	}

	for (int i = 0; i < map.bullets.size();) {
		if (map.bullets[i].update(map, raptors)) {
			map.bullets[i] = map.bullets.back();
			map.bullets.pop_back();
		} else {
			i++;
		}
	}

	for (int j = 0; j < map.bullets.size(); j++) {
		for (int i = 0; i < raptors.size();) {
			if (raptors[i].getBoundingBox().overlaps(
					map.bullets[j].getBoundingBox())) {
				raptors[i].health -= map.bullets[j].damage;
				if (raptors[i].health <= 0) {
					raptors[i] = raptors.back();
					raptors.pop_back();
				} else {
					i++;
				}
				map.bullets[j].shouldDie = true;
			} else {
				i++;
			}
		}
	}
}
