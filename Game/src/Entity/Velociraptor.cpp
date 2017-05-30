/*
 * Velociraptor.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#include <Engine/Include/Vertex.h>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>
#include <glm/glm.hpp>
#include "Velociraptor.h"
#include <iostream>
#include "../Dungeon/TileFlags.h"

Velociraptor::Velociraptor() :
		GameEntity(VELOCIRAPTOR_SIZE) {
	int rng = std::rand() % 4;
	switch (rng) {
	case 0:
		currentDir = UP;
		break;
	case 1:
		currentDir = DOWN;
		break;
	case 2:
		currentDir = RIGHT;
		break;
	case 3:
		currentDir = LEFT;
		break;
	}
}

Velociraptor::~Velociraptor() {
}

void Velociraptor::render(Engine::SpriteBatch& batcher) const {
	static Engine::GL_Texture playerTexture =
			Engine::ResourceManager::getTexture(
					"jimmyjump_pack/PNG/CharacterLeft_Jump.png");
	glm::vec4 uvRect(1, 1, -1, -1);
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 destRect(_position.x, _position.y, VELOCIRAPTOR_SIZE,
			VELOCIRAPTOR_SIZE);
	batcher.draw(destRect, uvRect, playerTexture.id, 0, color);
}

void Velociraptor::ai(GameEntity& target, Dungeon& map) {
	glm::ivec2 currentPos((_position.x + renderSize / 2) / map.scale,
			(_position.y + renderSize / 2) / map.scale);

	glm::vec2 targetLocation = target.getPosition();
	glm::ivec2 targetPos((targetLocation.x + target.renderSize / 2) / map.scale,
			(targetLocation.y + target.renderSize / 2) / map.scale);

	if (targetPos == currentPos) {
		target.kill();
	} else {

		unsigned int up = map.queryTile(currentPos + UP);
		unsigned int down = map.queryTile(currentPos + DOWN);
		unsigned int left = map.queryTile(currentPos + LEFT);
		unsigned int right = map.queryTile(currentPos + RIGHT);

		glm::vec2 dir(0, 0);

		unsigned int max = 0;
		if (up > max) {
			max = up;
			dir = UP;
		}
		if (down > max) {
			max = down;
			dir = DOWN;
		}
		if (left > max) {
			max = left;
			dir = LEFT;
		}
		if (right > max) {
			max = right;
			dir = RIGHT;
		}

		if (max == 0) {
			if (currentDir == UP) {
				if (!(map.tileArray[map.getIndex(currentPos.x, currentPos.y + 1)]
						& NAVIGABLE)) {
					int rng = std::rand() % 3;
					switch (rng) {
					case 0:
						currentDir = LEFT;
						break;
					case 1:
						currentDir = DOWN;
						break;
					case 2:
						currentDir = RIGHT;
						break;
					}
				}
			}
			if (currentDir == DOWN) {
				if (!(map.tileArray[map.getIndex(currentPos.x, currentPos.y - 1)]
						& NAVIGABLE)) {
					int rng = std::rand() % 3;
					switch (rng) {
					case 0:
						currentDir = LEFT;
						break;
					case 1:
						currentDir = UP;
						break;
					case 2:
						currentDir = RIGHT;
						break;
					}
				}
			}
			if (currentDir == LEFT) {
				if (!(map.tileArray[map.getIndex(currentPos.x - 1, currentPos.y)]
						& NAVIGABLE)) {
					int rng = std::rand() % 3;
					switch (rng) {
					case 0:
						currentDir = DOWN;
						break;
					case 1:
						currentDir = UP;
						break;
					case 2:
						currentDir = RIGHT;
						break;
					}
				}
			}
			if (currentDir == RIGHT) {
				if (!(map.tileArray[map.getIndex(currentPos.x + 1, currentPos.y)]
						& NAVIGABLE)) {
					int rng = std::rand() % 3;
					switch (rng) {
					case 0:
						currentDir = DOWN;
						break;
					case 1:
						currentDir = UP;
						break;
					case 2:
						currentDir = LEFT;
						break;
					}
				}
			}
		}

		if (max != 0) {
			currentDir = dir;
		}
		if (currentDir == UP || currentDir == DOWN) {
			_position.x = currentPos.x * map.scale + map.scale / 2
					- renderSize / 2;
		} else {
			_position.y = currentPos.y * map.scale + map.scale / 2
					- renderSize / 2;
		}
		move(currentDir, map);
	}
}

void Velociraptor::kill() {

}
