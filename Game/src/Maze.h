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

enum gridType
	: char {
		ROOM, NONE, HALLWAY
};

class Maze {
public:
	Maze();
	virtual ~Maze();

	gridType grid[100][100];

	void makeRooms();
	void setSeeds();
	void makeHallways();
private:
	std::vector<glm::ivec2> _seeds;
};

#endif /* MAZE_H_ */
