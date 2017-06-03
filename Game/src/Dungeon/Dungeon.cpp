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
#include "../Entity/Velociraptor.h"
#include "Dependencies\SDL\lib\x86\SDL2.lib"
#include "Dependencies\SDL\lib\x86\SDL2main.lib"
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

void Dungeon::spawnVelociraptor() {
	Velociraptor newRaptor;
	bool velGood = false;
	while (!velGood) {
		int x = std::rand() % gridSize;
		int y = std::rand() % gridSize;
		if (tileArray[getIndex(x, y)] & NAVIGABLE) {
			newRaptor.setPosition(glm::vec2(x * scale, y * scale)); //or something. probably find a seed and put them there
			velGood = true;
		}
	}
	velociraptors.push_back(newRaptor);
}

void Dungeon::playerWalkOnTile(glm::ivec2 tile) {
	_playerTrail[getIndex(tile.x, tile.y)] = SDL_GetTicks();
}

unsigned int Dungeon::queryTile(glm::ivec2 tile) {
	auto it = _playerTrail.find(getIndex(tile.x, tile.y));
	if (it != _playerTrail.end()) {
		return it->second;
	} else {
		return 0;
	}
}

int Dungeon::getIndex(int x, int y) const {
	return x * gridSize + y;
}

