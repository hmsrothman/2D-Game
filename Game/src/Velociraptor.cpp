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

	//GameEntity::move(dir, map);
}
