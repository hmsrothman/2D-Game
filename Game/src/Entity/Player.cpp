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
#include "Dependencies\SDL\lib\x86\SDL2.lib"

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
	static Engine::GLTexture playerTexture =
			Engine::ResourceManager::getTexture("Resources/archaeologist.png");
	glm::vec4 uvRect(1, 1, -1, -1);
	Engine::Color color(255,255,255,255);

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

void Player::update(std::vector<Bullet>& bullets, Dungeon& map) {
	GameEntity::update();
	if (_currentGun != -1) {
		glm::vec2 dir = _inputManager->getMouseCoords();
		dir = _camera->convertScreenToWorld(dir);
		dir -= _position;
		dir = glm::normalize(dir);
		_guns[_currentGun]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
				_position, dir, bullets);
	}

	if (_inputManager->isKeyPressed(SDLK_w)) {
		move(glm::vec2(0, speed), map);
	}
	if (_inputManager->isKeyPressed(SDLK_s)) {

		move(glm::vec2(0, -speed), map);
	}
	if (_inputManager->isKeyPressed(SDLK_a)) {

		move(glm::vec2(-speed, 0), map);
	}
	if (_inputManager->isKeyPressed(SDLK_d)) {
		move(glm::vec2(speed, 0), map);
	}
}

