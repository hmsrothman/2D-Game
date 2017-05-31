/*
 * DungeonRenderer.cpp
 *
 *  Created on: May 29, 2017
 *      Author: Simon
 */

#include "DungeonRenderer.h"
#include "TileFlags.h"
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>
#include "../Entity/Velociraptor.h"

DungeonRenderer::DungeonRenderer() {

}

DungeonRenderer::~DungeonRenderer() {
}

void DungeonRenderer::render(Dungeon& dungeon,
		Engine::SpriteBatch& hallwayBatcher,
		Engine::SpriteBatch& otherBatcher) {

	for (int x = 0; x < dungeon.gridSize; x++) {
		for (int y = 0; y < dungeon.gridSize; y++) {
			//	std::cout << x << " , " << y << std::endl;
			if (dungeon.tileArray[dungeon.getIndex(x, y)] & NAVIGABLE) {
				renderSubTile(dungeon, hallwayBatcher, otherBatcher, x, y,
						dungeon.tileArray[dungeon.getIndex(x, y)] & TILE_TYPE);
			}
		}
	}
//	std::cout << count << std::endl;
	for (int i = 0; i < dungeon.velociraptors.size(); i++) {
		dungeon.velociraptors[i].render(otherBatcher);
	}

	for(auto& bullet:dungeon.bullets){
		bullet.draw(otherBatcher);
	}
}

void DungeonRenderer::renderSubTile(const Dungeon& dungeon,
		Engine::SpriteBatch&hallwayBatcher, Engine::SpriteBatch&otherBatcher,
		int x, int y, unsigned char tileType) {
	static Engine::GL_Texture doorway = Engine::ResourceManager::getTexture(
			"doorway.png");
	static Engine::GL_Texture hallway = Engine::ResourceManager::getTexture(
			"hallway.png");
	static Engine::GL_Texture room = Engine::ResourceManager::getTexture(
			"room.png");
	static Engine::GL_Texture other = Engine::ResourceManager::getTexture(
			"jimmyJump_pack/PNG/AngryCloud.png");

	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct

	unsigned int texture = 0;

	switch (tileType) {
	case ROOM:
		texture = room.id;
		otherBatcher.draw(
				glm::vec4(x * dungeon.scale, y * dungeon.scale, dungeon.scale,
						dungeon.scale), uvRect, texture, 0, color);
		break;
	case HALLWAY:
		texture = hallway.id;
		hallwayBatcher.draw(
				glm::vec4(x * dungeon.scale, y * dungeon.scale, dungeon.scale,
						dungeon.scale), uvRect, texture, 0, color);
		break;
	case DOORWAY:
		texture = doorway.id;
		otherBatcher.draw(
				glm::vec4(x * dungeon.scale, y * dungeon.scale, dungeon.scale,
						dungeon.scale), uvRect, texture, 0, color);
		break;
	default:
		texture = other.id;
		otherBatcher.draw(
				glm::vec4(x * dungeon.scale, y * dungeon.scale, dungeon.scale,
						dungeon.scale), uvRect, texture, 0, color);
		break;
	}
}
