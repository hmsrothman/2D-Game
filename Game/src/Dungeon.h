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
#include <unordered_map>
#include <random>
#include <stack>
#include <memory>
#include <Engine/Include/SpriteBatch.h>
#include <map>

class Velociraptor;

struct vecCompare: public std::binary_function<glm::ivec2, glm::ivec2, bool> {
	bool operator()(const glm::ivec2& lhs, const glm::ivec2& rhs) const {
		return lhs.x + lhs.y < rhs.x + rhs.y;
	}
};

/**
 * last 4 bits are walls
 * 5th to last bit is bool visited by maze gen
 * 6th to last bit is bool isRoom
 */

enum TileFlags
	:unsigned char {
		WALLS = 0b00001111,
	TILE_TYPE = 0b01100000,
	NONE = 0,
	LEFT = 0b00000001,
	RIGHT = 0b00000010,
	UP = 0b00000100,
	DOWN = 0b00001000,
	VISITED = 0b00010000,
	ROOM = 0b00100000,
	HALLWAY = 0b01000000,
	DOORWAY = 0b01100000,
	NAVIGABLE = 0b10000000,
};

struct MazeGenTile {
	glm::ivec2 pos;
	unsigned char flags;
	MazeGenTile() :
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

	const static int ROOM_SIZE_MEAN = 5;
	const static int ROOM_SIZE_VAR = 1;
	const static int GRID_SIZE = 100;
	const static int GRID_SCALE = 20;
	const static int PATH_WIDTH = GRID_SCALE / 2;

	int roomAttempts = 400;
	int mazeBreakChance = 500; //inverse of chance hallway randomly tunnels to another

	std::vector<Rectangle> rooms;

	MazeGenTile tiles[GRID_SIZE][GRID_SIZE];
	unsigned char subTiles[GRID_SIZE * 3][GRID_SIZE * 3];

	void render(Engine::SpriteBatch &hallwayBatcher,
			Engine::SpriteBatch& otherBatcher);
	void prepare();
	void placeRooms();
	void iterateMaze();
	void fillSubTiles();
	std::vector<Velociraptor> velociraptors;

	void playerWalkOnTile(glm::ivec2 tile);
	unsigned int queryTile(glm::ivec2 tile);
private:
	void buildHallways();
	void breakMaze();
	void cullDeadEnds();
	void tunnel(glm::ivec2 start, unsigned char dir, unsigned char otherFlags);

	void renderSubTile(Engine::SpriteBatch&hallwayBatcher,
			Engine::SpriteBatch&otherBatcher, int x, int y,
			unsigned char tileType);

	MazeGenTile* current;
	MazeGenTile *start;
	std::stack<MazeGenTile*> backtrack;

	std::map<glm::ivec2, unsigned int, vecCompare> _playerTrail;

};

#endif /* DUNGEON_H_ */
