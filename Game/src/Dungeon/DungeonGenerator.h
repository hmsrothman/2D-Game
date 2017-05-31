/*
 * DungeonGenerator.h
 *
 *  Created on: May 29, 2017
 *      Author: Simon
 */

#ifndef DUNGEONGENERATOR_H_
#define DUNGEONGENERATOR_H_

#include "../Rectangle.h"
#include <stack>
#include <vector>
#include "TileFlags.h"

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

class DungeonGenerator {
public:
	DungeonGenerator();
	virtual ~DungeonGenerator();

	void generate(unsigned char** out_tileArray, int* out_gridSize);

private:
	int _roomSizeMean = 5;
	int _roomSizeVar = 1;
	int _roomAttempts = 400;
	int _mazeBreakChance = 1;
	const static int _gridSize = 100;

	MazeGenTile* _current = nullptr;
	MazeGenTile *_start = nullptr;
	std::stack<MazeGenTile*> _backtrack;

	std::vector<Rectangle> rooms;

	MazeGenTile tiles[_gridSize][_gridSize];
	;
	unsigned char* subTiles = nullptr;

	void prepare();
	void placeRooms();
	void iterateMaze();
	void fillSubTiles();
	void buildHallways();
	void breakMaze();
	void cullDeadEnds();
	void tunnel(glm::ivec2 start, unsigned char dir, unsigned char otherFlags);

	int getIndex(int x, int y) {
		return x * _gridSize * 3 + y;
	}
};

#endif /* DUNGEONGENERATOR_H_ */
