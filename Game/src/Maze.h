/*
 * Maze.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <vector>
#include <glm/glm.hpp>

enum tileID
	: char {
		ROOM, NONE, HALLWAY
};

class Maze {
public:
	Maze();
	virtual ~Maze();

	const int SIZE_X = 100;
	const int SIZE_Y = 100;

	const int TILE_WIDTH = 100;

	tileID grid[100][100]; //this shouldn't be too expensive? they're only chars

	void makeRooms();
	void setSeeds();
	void makeHallways();

private:
	std::vector<glm::ivec2> _seeds;
};

#endif /* MAZE_H_ */
