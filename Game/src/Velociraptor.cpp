/*
 * Velociraptor.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#include "Velociraptor.h"
#include <Engine/Include/Vertex.h>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GameEntity.h"


Velociraptor::Velociraptor() :
		GameEntity(VELOCIRAPTOR_SIZE) {

}

Velociraptor::~Velociraptor() {
}

void Velociraptor::render(Engine::SpriteBatch& batcher) { //this doesn't work for some reason
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
void Velociraptor::ai(Engine::Entity target, Dungeon map) {
	//convert from screen coords to maze coords
	//checks the value of the tiles around it
	//find the biggest value and move in that direction
	/*
	glm::ivec2 pos(0, 0);//'where we are'
	glm::ivec2 dir(0, 0);//empty
	glm::ivec2 dest(0, 0);//empty
	int max = -1;

	dest = pos + glm::ivec2(1, 0);
	if (map.queryTile(dest) > max) {
		max = map.queryTile(dest);
		dir = pos - dest;
	}
	dest = pos - glm::ivec2(1, 0);
	if (map.queryTile(dest) > max) {
		max = map.queryTile(dest);
		dir = pos - dest;
	}
	dest = pos + glm::ivec2(0, 1);
	if (map.queryTile(dest) > max) {
		max = map.queryTile(dest);
		dir = pos - dest;
	}
	dest = pos - glm::ivec2(0,1);
	if (map.queryTile(dest) > max) {
		max = map.queryTile(dest);
		dir = pos - dest;
	}

	GameEntity::move(dir, map);
	*/

}
