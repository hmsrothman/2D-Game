/*
 * Player.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include <iostream>
#include <unordered_set>
#include <Engine/Include/ResourceManager.h>
#include <Engine/Include/Vertex.h>
#include "GameEntity.h"
#include "Player.h"
#include "../Dungeon/Dungeon.h"
#include "Dependencies/SDL/lib/SDL2.lib"

class Bullet;

Player::Player(Engine::InputManager* inputManager, Engine::Camera2D *camera) :
		GameEntity(10), _inputManager(inputManager), _camera(camera) {
}

Player::~Player() {
}

void Player::move(glm::vec2 displacement, Dungeon& map) {
	GameEntity::move(displacement, map);
	map.playerWalkOnTile(
			glm::ivec2((_position.x + renderSize / 2) / map.scale,
					(_position.y + renderSize / 2) / map.scale));
}

void Player::render(Engine::SpriteBatch& batcher) const {
	static Engine::GL_Texture playerTexture =
			Engine::ResourceManager::getTexture("archaeologist.png");
	glm::vec4 uvRect(1, 1, -1, -1);
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 destRect(_position.x, _position.y, renderSize, renderSize);
	batcher.draw(destRect, uvRect, playerTexture.id, 0, color);
}

void Player::kill() {
	std::cout << "u ded" << std::endl;
	isded = true;
}

void Player::addGun(Gun * gun) {
	_guns.push_back(gun);
	if (_currentGun == -1) {
		_currentGun = 0;
	}
}

void Player::update(std::vector<Bullet>& bullets) {
	if (_currentGun != -1) {
		glm::vec2 dir = _inputManager->getMouseCoords();
		dir = _camera->convertScreenToWorld(dir);
		dir -=_position;
		dir = glm::normalize(dir);

		_guns[_currentGun]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
				_position, dir, bullets);
	}
}

