/*
 * Dungeon.cpp
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#include "Dungeon.h"
#include <Engine/Include/Vertex.h>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>
#include "Velociraptor.h"
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "DungeonGenerator.h"
#include "TileFlags.h"
#include <iostream>
Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
	delete (tileArray);
}

void Dungeon::genMap() {
	DungeonGenerator gen;
	gen.generate(&tileArray, &gridSize);
}

void Dungeon::render(Engine::SpriteBatch& hallwayBatcher,
		Engine::SpriteBatch& otherBatcher) {
	//for (int x = 0; x < GRID_SIZE; x++) {
	/*for (int y = 0; y < GRID_SIZE; y++) {
	 char roomType = tiles[x][y].flags & TILE_TYPE;
	 switch (roomType) {
	 case ROOM:
	 renderRoom(batcher, x, y);
	 break;
	 case HALLWAY:
	 renderHallway(batcher, x, y);
	 break;
	 case DOOR:
	 renderDoor(batcher, x, y);
	 }
	 }*/

	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			//	std::cout << x << " , " << y << std::endl;
			if (tileArray[getIndex(x, y)] & NAVIGABLE) {
				renderSubTile(hallwayBatcher, otherBatcher, x, y,
						tileArray[getIndex(x, y)] & TILE_TYPE);
			}
		}
	}
//	std::cout << count << std::endl;
	for (int i = 0; i < velociraptors.size(); i++) {
		velociraptors[i].render(otherBatcher);
	}
}

void Dungeon::renderSubTile(Engine::SpriteBatch&hallwayBatcher,
		Engine::SpriteBatch&otherBatcher, int x, int y,
		unsigned char tileType) {
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
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	case HALLWAY:
		texture = hallway.id;
		hallwayBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	case DOORWAY:
		texture = doorway.id;
		otherBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	default:
		texture = other.id;
		otherBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	}
}

void Dungeon::playerWalkOnTile(glm::ivec2 tile) {
	_playerTrail[tile] = SDL_GetTicks();
}

unsigned int Dungeon::queryTile(glm::ivec2 tile) {
	auto it = _playerTrail.find(tile);
	if (it != _playerTrail.end()) {
		return it->second;
	} else {
		return 0;
	}
}

int Dungeon::getIndex(int x, int y) {
	return x * gridSize + y;
}

