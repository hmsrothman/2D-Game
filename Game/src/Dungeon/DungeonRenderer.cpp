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

void DungeonRenderer::renderRaptors(Dungeon& dungeon,
		Engine::SpriteBatch &batcher) {
	for (int i = 0; i < dungeon.velociraptors.size(); i++) {
		dungeon.velociraptors[i].render(batcher);
	}
	for (auto& bullet : dungeon.bullets) {
		bullet.draw(batcher);
	}
}

void DungeonRenderer::renderDungeon(Dungeon& dungeon,
		Engine::SpriteBatch& batcher) {

	for (int x = 0; x < dungeon.gridSize; x++) {
		for (int y = 0; y < dungeon.gridSize; y++) {
			//	std::cout << x << " , " << y << std::endl;
			if (dungeon.tileArray[dungeon.getIndex(x, y)] & NAVIGABLE) {
				renderSubTile(dungeon, batcher, x, y,
						dungeon.tileArray[dungeon.getIndex(x, y)] & TILE_TYPE);
			}
		}
	}

}

void DungeonRenderer::renderSubTile(const Dungeon& dungeon,
		Engine::SpriteBatch& batcher, int x, int y, unsigned char tileType) {
	static Engine::GLTexture doorway = Engine::ResourceManager::getTexture(
			"resources/doorway.png");
	static Engine::GLTexture hallway = Engine::ResourceManager::getTexture(
			"resources/hallway.png");
	static Engine::GLTexture room = Engine::ResourceManager::getTexture(
			"resources/room.png");
	static Engine::GLTexture other = Engine::ResourceManager::getTexture(
			"resources/jimmyJump_pack/PNG/AngryCloud.png");

	Engine::Color color(255, 255, 255, 255);

	glm::vec4 uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct

	unsigned int texture = 0;

	switch (tileType) {
	case ROOM:
		texture = room.id;
		break;
	case HALLWAY:
		texture = hallway.id;
		break;
	case DOORWAY:
		texture = doorway.id;
		break;
	default:
		texture = other.id;
		break;
	}
	batcher.draw(
			glm::vec4(x * dungeon.scale, y * dungeon.scale, dungeon.scale,
					dungeon.scale), uvRect, texture, 0, color);
}
