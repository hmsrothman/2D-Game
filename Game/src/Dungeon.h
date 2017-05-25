/*
 * Dungeon.h
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <vector>
#include "Rectangle.h"
#include <map>
#include <random>
#include <stack>
#include <memory>
#include <Engine/Include/SpriteBatch.h>

/**
 * last 4 bits are walls
 * 5th to last bit is bool visited by maze gen
 * 6th to last bit is bool isRoom
 */

enum TileFlags
	:char {
		WALLS = 0b00001111,
	TILE_TYPE = 0b01100000,
	LEFT = 0b00000001,
	RIGHT = 0b00000010,
	UP = 0b00000100,
	DOWN = 0b00001000,
	VISITED = 0b00010000,
	ROOM = 0b00100000,
	HALLWAY = 0b01000000,
	DOOR = 0b01100000
};

struct Tile {
	glm::ivec2 pos;
	char flags;
	Tile() :
			pos(0, 0), flags(0) {
	}
	void setTileType(char roomType) {
		flags &= ~TILE_TYPE;
		flags |= roomType;
	}
};

class Dungeon {
public:
	Dungeon();
	virtual ~Dungeon();

	void generate();

	const static int ROOM_SIZE_MEAN = 10;
	const static int ROOM_SIZE_VAR = 1;
	const static int GRID_SIZE = 100;
	const static int GRID_SCALE = 100;
	const static int PATH_WIDTH = GRID_SCALE / 2;

	int roomAttempts = 400;
	int mazeBreakChance = 500; //inverse of chance hallway randomly tunnels to another

	std::vector<Rectangle> rooms;

	Tile tiles[GRID_SIZE][GRID_SIZE];

	void render(Engine::SpriteBatch &batcher);
private:

	void placeRooms();
	void buildHallways();
	void breakMaze();
	void cullDeadEnds();
	void tunnel(glm::ivec2 start, char dir, char otherFlags);
	void iterateMaze();
	void prepare();

	void renderHallway(Engine::SpriteBatch &batcher, int x, int y);
	void renderRoom(Engine::SpriteBatch &batcher, int x, int y);
	void renderDoor(Engine::SpriteBatch &batcher, int x, int y);

	Tile* current;
	Tile *start;
	std::stack<Tile*> backtrack;

};

#endif /* DUNGEON_H_ */
