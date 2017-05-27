/*
 * Player.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include "Player.h"
#include <iostream>
#include <unordered_set>
#include <Engine/Include/ResourceManager.h>
#include <Engine/Include/Vertex.h>
#include "Dungeon.h"
#include "GameEntity.h"

Player::Player() :
		GameEntity(PLAYER_SIZE) {
}

Player::~Player() {
}

<<<<<<< HEAD
=======
void Player::move(glm::vec2 displacement, Dungeon& map) {
	GameEntity::move(displacement, map);
	map.playerWalkOnTile(
			glm::ivec2(_position.x / map.GRID_SCALE,
					_position.y / map.GRID_SCALE));
}
>>>>>>> refs/remotes/origin/master

void Player::render(Engine::SpriteBatch& batcher) { //this doesn't work for some reason
	static Engine::GL_Texture playerTexture =
			Engine::ResourceManager::getTexture(
					"jimmyjump_pack/PNG/AngryCloud.png");
	glm::vec4 uvRect(1, 1, -1, -1);
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 destRect(_position.x, _position.y, PLAYER_SIZE, PLAYER_SIZE);
	batcher.draw(destRect, uvRect, playerTexture.id, 0, color);
}
