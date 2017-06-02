/*
 * DungeonGenerator.cpp
 *
 *  Created on: May 29, 2017
 *      Author: Simon
 */



#include <cstdlib>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <Engine/Include/Vertex.h>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>
#include "Game/src/Entity/Velociraptor.h"

#include <SDL.h>

#include "DungeonGenerator.h"
#include <random>


DungeonGenerator::DungeonGenerator() {
}

DungeonGenerator::~DungeonGenerator() {

}

void DungeonGenerator::generate(unsigned char** out_tileArray,
		int* out_gridSize) {

	subTiles = (unsigned char*) malloc(
			(_gridSize * 3) * (_gridSize * 3) * sizeof(unsigned char));
	prepare();
	std::cout << "prep" << std::endl;
	placeRooms();
	std::cout << "place" << std::endl;
	buildHallways();
	std::cout << "buiild" << std::endl;
	breakMaze();
	std::cout << "break"<<std::endl;
	cullDeadEnds();
	std::cout << "cull" << std::endl;
	fillSubTiles();
	std::cout << "fill" << std::endl;
	velociraptors.emplace_back();
	std::cout << "velo++" << std::endl;

}

void DungeonGenerator::prepare() {
	//init array
	for (int x = 0; x < _gridSize; x++) {
		for (int y = 0; y < _gridSize; y++) {
			tiles[x][y].pos = glm::ivec2(x, y);
			if (x == 0 || y == 0 || x == _gridSize - 1 || y == _gridSize - 1) {
				tiles[x][y].flags |= VISITED;
			}
		}
	}
	for (int x = 0; x < _gridSize * 3; x++) {
		for (int y = 0; y < _gridSize * 3; y++) {
			subTiles[getIndex(x, y)] = 0;
		}
	}

	//prepare for hallwaygen
	_start = &tiles[1][1];
	_start->flags |= VISITED | HALLWAY; //set it to visted and hallway
	_backtrack.push(_start);
	_current = _start;
}

void DungeonGenerator::placeRooms() {

	//rooms.emplace_back(0, 0, 5, 5);
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(_roomSizeMean, _roomSizeVar);


	for (int i = 0; i < _roomAttempts; i++) {
		int sizeX = 0;
		int sizeY = 0;
		while (sizeX <= 1) {
			sizeX = distribution(generator);
		}
		while (sizeY <= 1) {
			sizeY = distribution(generator);
		}

		int x = std::rand() % (_gridSize - sizeX - 2) + 1;
		int y = std::rand() % (_gridSize - sizeY - 2) + 1;

		Rectangle newRect(x, y, sizeX, sizeY);

		bool overlap = false;
		for (int rect = 0; rect < rooms.size(); rect++) {
			if (newRect.overlaps(rooms[rect])) {
				overlap = true;
			}
		}

		if (overlap) {
			continue;
		} else {

			rooms.push_back(newRect);
		}
	}

	for (int i = 0; i < rooms.size(); i++) {
		Rectangle rect = rooms[i];
		for (int x = rect.position.x; x < rect.position.x + rect.position.z;
				x++) {
			for (int y = rect.position.y; y < rect.position.y + rect.position.w;
					y++) {
				tiles[x][y].flags |= UP | DOWN | LEFT | RIGHT | VISITED
						| NAVIGABLE;
				tiles[x][y].setTileType(ROOM);
				if (x == rect.position.x) { //if on left, close left wall
					tiles[x][y].flags &= ~LEFT;
				}
				if (x == rect.position.x + rect.position.z) { //if on right, close right wall
					tiles[x][y].flags &= ~RIGHT;
				}
				if (y == rect.position.y) { //if down, close that wall
					tiles[x][y].flags &= ~DOWN;
				}
				if (y == rect.position.y + rect.position.w) { //if up, close that wall
					tiles[x][y].flags &= ~UP;
				}
			}
		}
	}
}

void DungeonGenerator::buildHallways() {
	while (!_backtrack.empty()) {
		iterateMaze();
	}
}

void DungeonGenerator::iterateMaze() {
	bool left = false, right = false, up = false, down = false;
	_current->flags |= VISITED;
	if (_current->pos.x + 1 < _gridSize) {
		if ((tiles[_current->pos.x + 1][_current->pos.y].flags & VISITED)
				< VISITED) {
			right = true;
		}
	}
	if (_current->pos.x - 1 >= 0) {
		if ((tiles[_current->pos.x - 1][_current->pos.y].flags & VISITED)
				< VISITED) {
			left = true;
		}
	}
	if (_current->pos.y + 1 < _gridSize) {
		if ((tiles[_current->pos.x][_current->pos.y + 1].flags & VISITED)
				< VISITED) {
			up = true;
		}
	}
	if (_current->pos.y - 1 >= 0) {
		if ((tiles[_current->pos.x][_current->pos.y - 1].flags & VISITED)
				< VISITED) {
			down = true;
		}
	}

	if (up | right | left | down) {
		int dir = 1 << (std::rand() % 4); //2^n?
		switch (dir) {
		case RIGHT:
			if (right) {
				tunnel(_current->pos, dir, VISITED | NAVIGABLE);
				_current = &(tiles[_current->pos.x + 1][_current->pos.y]);
				_backtrack.push(_current);
			}
			break;
		case LEFT:
			if (left) {
				tunnel(_current->pos, dir, VISITED | NAVIGABLE);
				_current = &(tiles[_current->pos.x - 1][_current->pos.y]);
				_backtrack.push(_current);
			}
			break;
		case UP:
			if (up) {
				tunnel(_current->pos, dir, VISITED | NAVIGABLE);
				_current = &tiles[_current->pos.x][_current->pos.y + 1];
				_backtrack.push(_current);
			}
			break;
		case DOWN:
			if (down) {
				tunnel(_current->pos, dir, VISITED | NAVIGABLE);
				_current = &(tiles[_current->pos.x][_current->pos.y - 1]);
				_backtrack.push(_current);
			}
			break;
		}
		_current->setTileType(HALLWAY);
	} else if (!_backtrack.empty()) {
		_current = _backtrack.top();
		_backtrack.pop();
	} else {
	}
}

void DungeonGenerator::breakMaze() {
	//go through each tile and randomly have it connect out
	for (int x = 2; x < _gridSize - 2; x++) { //outer two are excluded because they could tunnel to nothing
		for (int y = 2; y < _gridSize - 2; y++) { //note that outermost is a buffer to ease maze gen
			if ((tiles[x][y].flags & TILE_TYPE) == HALLWAY) {
				int prb = std::rand() % _mazeBreakChance;
				if (prb == 1) {
					int dir = 1 << (std::rand() % 4); //2^n?
					tunnel(glm::ivec2(x, y), dir, 0);
					switch (dir) {
					case UP:
						if ((tiles[x][y + 1].flags & TILE_TYPE) == ROOM) {
							tiles[x][y + 1].setTileType(DOORWAY);
						}
						break;
					case DOWN:
						if ((tiles[x][y - 1].flags & TILE_TYPE) == ROOM) {
							tiles[x][y - 1].setTileType(DOORWAY);
						}
						break;
					case RIGHT:
						if ((tiles[x + 1][y].flags & TILE_TYPE) == ROOM) {
							tiles[x + 1][y].setTileType(DOORWAY);
						}
						break;
					case LEFT:
						if ((tiles[x - 1][y].flags & TILE_TYPE) == ROOM) {
							tiles[x - 1][y].setTileType(DOORWAY);
						}
						break;
					}
				}
			}
		}
	}
	std::cout << "make entrance" << std::endl;
	//randomly give each room two entrances
	for (int i = 0; i < rooms.size(); i++) {
		bool left = false, right = false, up = false, down = false;
		if (rooms[i].position.x > 1) {
			left = true;
		}
		if (rooms[i].position.y > 1) {
			down = true;
		}
		if (rooms[i].position.x + rooms[i].position.z - 1 < _gridSize - 1) {
			right = true;
		}
		if (rooms[i].position.y + rooms[i].position.w - 1 < _gridSize - 1) {
			up = true;
		}
		if (right || up || down || left) {
			int entrancesMade = 0;
			while (entrancesMade < 2) {
				int dir = 1 << (std::rand() % 4);
				switch (dir) {
				case RIGHT:
					if (right) {
						int dy = std::rand() % (int) (rooms[i].position.w - 1);
						glm::ivec2 pos(
								rooms[i].position.x + rooms[i].position.z - 1,
								rooms[i].position.y + dy);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, RIGHT, 0);
						entrancesMade++;
					}
					break;
				case LEFT:
					if (left) {
						int dy = std::rand() % (int) (rooms[i].position.w - 1);
						glm::ivec2 pos(rooms[i].position.x,
								rooms[i].position.y + dy);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, LEFT, 0);
						entrancesMade++;
					}
					break;
				case DOWN:
					if (down) {
						int dx = std::rand() % (int) (rooms[i].position.z - 1);
						glm::ivec2 pos(rooms[i].position.x + dx,
								rooms[i].position.y);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, DOWN, 0);
						entrancesMade++;
					}
					break;
				case UP:
					if (up) {
						int dx = std::rand() % (int) (rooms[i].position.z - 1);
						glm::ivec2 pos(rooms[i].position.x + dx,
								rooms[i].position.y + rooms[i].position.w - 1);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, UP, 0);
						entrancesMade++;
					}
					break;
				}
			}
		}
	}
}

void DungeonGenerator::cullDeadEnds() {
	int numCulled = 1;
	while (numCulled != 0) {
		numCulled = 0;
		for (int x = 0; x < _gridSize; x++) {
			for (int y = 0; y < _gridSize; y++) {
				if ((tiles[x][y].flags & TILE_TYPE) == HALLWAY) {
					char rooms = tiles[x][y].flags & WALLS;
					if (rooms == LEFT || rooms == RIGHT || rooms == UP
							|| rooms == DOWN) {
						++numCulled;
						tiles[x][y].flags &= ~TILE_TYPE;
						tiles[x][y].flags &= ~WALLS;
						tiles[x][y].flags &= ~NAVIGABLE;

						tiles[x - 1][y].flags &= ~RIGHT;
						tiles[x + 1][y].flags &= ~LEFT;
						tiles[x][y - 1].flags &= ~UP;
						tiles[x][y + 1].flags &= ~DOWN;
					}
				}
			}
		}
	}
}

void DungeonGenerator::fillSubTiles() {
	int sx = 0, sy = 0;
	for (int x = 0; x < _gridSize; x++) {
		for (int y = 0; y < _gridSize; y++) {
			if (tiles[x][y].flags & NAVIGABLE) {
				sx = 3 * x;
				sy = 3 * y;
				char tileType = tiles[x][y].flags & TILE_TYPE;
				if (tileType == HALLWAY) {
					for (int dx = 0; dx < 3; dx++) {
						for (int dy = 0; dy < 3; dy++) {
							subTiles[getIndex(sx + dx, sy + dy)] = tileType;
							subTiles[getIndex(sx + dx, sy + dy)] &= ~NAVIGABLE;
						}
					}

					subTiles[getIndex(sx + 1, sy + 1)] |= NAVIGABLE;

					if (tiles[x][y].flags & LEFT) {
						subTiles[getIndex(sx, sy + 1)] |= NAVIGABLE;
					}

					if (tiles[x][y].flags & RIGHT) {
						subTiles[getIndex(sx + 2, sy + 1)] |= NAVIGABLE;
					}

					if (tiles[x][y].flags & UP) {
						subTiles[(sx + 1) * _gridSize * 3 + sy + 2] |=
								NAVIGABLE;
					}

					if (tiles[x][y].flags & DOWN) {
						subTiles[(sx + 1) * _gridSize * 3 + sy] |= NAVIGABLE;
					}
				} else if (tileType == ROOM || tileType == DOORWAY) {
					for (int dx = 0; dx < 3; dx++) {
						for (int dy = 0; dy < 3; dy++) {
							subTiles[(sx + dx) * _gridSize * 3 + sy + dy] =
									tileType | NAVIGABLE;
						}
					}
				}
			}
		}
	}
}

void DungeonGenerator::tunnel(glm::ivec2 start, unsigned char dir,
		unsigned char otherFlags) {
	switch (dir) {
	case UP:
		tiles[start.x][start.y].flags |= UP | otherFlags;
		tiles[start.x][start.y + 1].flags |= DOWN | otherFlags;
		break;
	case DOWN:
		tiles[start.x][start.y].flags |= DOWN | otherFlags;
		tiles[start.x][start.y - 1].flags |= UP | otherFlags;
		break;
	case RIGHT:
		tiles[start.x][start.y].flags |= RIGHT | otherFlags;
		tiles[start.x + 1][start.y].flags |= LEFT | otherFlags;
		break;
	case LEFT:
		tiles[start.x][start.y].flags |= LEFT | otherFlags;
		tiles[start.x - 1][start.y].flags |= RIGHT | otherFlags;
		break;
	}
}

void Dungeon::playerWalkOnTile(glm::ivec2 tile) {
	//_playerTrail[tile] = SDL_GetTicks();
	//_trail[tile.x][tile.y] = SDL_GetTicks();
}

unsigned int Dungeon::queryTile(glm::ivec2 tile) {
	//return _trail[tile.x][tile.y];
	auto it = _playerTrail.find(tile);
	if (it != _playerTrail.end()) {
		return it->second;
	} else {
		return 0;
	}
}

