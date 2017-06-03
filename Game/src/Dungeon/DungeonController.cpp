/*
 * DungeonController.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Simon
 */

#include "DungeonController.h"
//#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "Dependencies\SDL\lib\x86\SDL2.lib"

DungeonController::DungeonController() {
	// TODO Auto-generated constructor stub

}

DungeonController::~DungeonController() {
	// TODO Auto-generated destructor stub
}

void DungeonController::updateRaptors(std::vector<Velociraptor>& raptors,
		GameEntity& target, Dungeon& map) {
	for (auto& raptor : raptors) {
		raptor.ai(target, map);
	}

	for (int i = 0; i < map.bullets.size();) {
		if (map.bullets[i].update(raptors)) {
			map.bullets[i] = map.bullets.back();
			map.bullets.pop_back();
		} else {
			i++;
		}
	}
}

void DungeonController::updatePlayer(Player& player,
		Engine::InputManager& inputManager, Dungeon& map,
		Engine::Camera2D& camera) {
	if (inputManager.isKeyPressed(SDLK_UP)) {
		player.move(glm::vec2(0, player.speed), map);
	}
	if (inputManager.isKeyPressed(SDLK_DOWN)) {

		player.move(glm::vec2(0, -player.speed), map);
	}
	if (inputManager.isKeyPressed(SDLK_LEFT)) {

		player.move(glm::vec2(-player.speed, 0), map);
	}
	if (inputManager.isKeyPressed(SDLK_RIGHT)) {
		player.move(glm::vec2(player.speed, 0), map);
	}

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {

	}
}
