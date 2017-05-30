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

int Dungeon::getIndex(int x, int y) const {
	return x * gridSize + y;
}

