/*
 * Maze.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include "Maze.h"
#include <cstdlib>
#include <iostream>

Maze::Maze() {
	for (int x = 0; x < SIZE_X; x++) { //initialize the array
		for (int y = 0; y < SIZE_Y; y++) {
			grid[x][y] = NONE;
		}
	}
}

Maze::~Maze() {

}

void Maze::setSeeds() { //does what it says on the tin
	_seeds.clear();
	for (int i = 0; i < 8; i++) {
		_seeds.push_back(glm::vec2(std::rand() % SIZE_X, std::rand() % SIZE_Y));
	}
}

void Maze::makeRooms() {
	const static int NUM_ITERATIONS = 20;

	//we need to double-buffer the outside layer for the fractal gen
	//this ensures that each iteration happens atomically
	//pointers avoid copying potentially large vectors back and forth

	std::vector<glm::ivec2> * tmp; //used for buffer swapping
	std::vector<glm::ivec2> *currentOutside = new std::vector<glm::ivec2>(0);
	std::vector<glm::ivec2> *nextOutside = new std::vector<glm::ivec2>(0);

	for (int seed = 0; seed < _seeds.size(); seed++) { //FOR EVERY SEED
		int seedX = _seeds[seed].x;
		int seedY = _seeds[seed].y;

		grid[seedX][seedY] = ROOM;
		currentOutside->emplace_back(seedX, seedY);

		for (int i = 0; i < NUM_ITERATIONS; i++) { //FOR EVERY ITERATION
			for (int j = 0; j < currentOutside->size(); j++) { //FOR EVERY OUTSIDE TILE
				glm::ivec2 currentRoom = (*currentOutside)[j];
				for (int dir = 0; dir < 4; dir++) { //FOR EVERY DIRECTION
					int propegate = std::rand() % 2; //this is a really shitty way to do this rng but whatever
					if (propegate == 1) { //then propegate
						switch (dir) {
						case 0: //DOWN
							if (currentRoom.y + 1 < SIZE_Y
									&& grid[currentRoom.x][currentRoom.y + 1]
											== NONE) {
								int y = currentRoom.y + 1; //Y coord of new room
								grid[currentRoom.x][y] = ROOM;
								nextOutside->emplace_back(currentRoom.x, y);
							}
							break;
						case 1: //RIGHT
							if (currentRoom.x + 1 < SIZE_X
									&& grid[currentRoom.x + 1][currentRoom.y]
											== NONE) {
								int x = currentRoom.x + 1; //X coord of new room
								grid[x][currentRoom.y] = ROOM;
								nextOutside->emplace_back(x, currentRoom.y);
							}
							break;
						case 2: //DOWN
							if (currentRoom.y - 1 >= 0
									&& grid[currentRoom.x][currentRoom.y - 1]
											== NONE) {
								int y = currentRoom.y - 1; //Y coord of new room
								grid[currentRoom.x][y] = ROOM;
								nextOutside->emplace_back(currentRoom.x, y);
							}
							break;
						case 3: //LEFT
							if (currentRoom.x - 1 >= 0
									&& grid[currentRoom.x - 1][currentRoom.y]
											== NONE) {
								int x = currentRoom.x - 1; //X coord of new room
								grid[x][currentRoom.y] = ROOM;
								nextOutside->emplace_back(x, currentRoom.y);
							}
							break;
						}
					}
				}
			}
			//time to swap our buffers
			tmp = nextOutside;
			nextOutside = currentOutside;
			currentOutside = tmp;
			nextOutside->clear();
		}

		delete (tmp);
		delete (nextOutside);
		delete (currentOutside);
	}

	/*grid[seedX][seedY] = ROOM;

	 const static int NUM_STEPS = 10;

	 int currentPosX, currentPosY;

	 currentPosX = seedX;
	 currentPosY = seedY;

	 for (int i = 0; i < NUM_STEPS; i++) {
	 int dir = std::rand() % 4;
	 int doubleStep = std::rand() % 3;
	 switch (dir) {
	 case 0: //DOWN
	 if (currentPosY + 1 < 100
	 && grid[currentPosX][currentPosY + 1] == NONE) {
	 currentPosY += 1;
	 grid[currentPosX][currentPosY] = ROOM;
	 } else {
	 i--;
	 continue;
	 }
	 break;
	 case 1: //RIGHT
	 if (currentPosX + 1 < 100
	 && grid[currentPosX + 1][currentPosY] == NONE) {
	 currentPosX += 1;
	 grid[currentPosX][currentPosY] = ROOM;
	 } else {
	 i--;
	 continue;
	 }
	 break;
	 case 2: //DOWN
	 if (currentPosY - 1 >= 0
	 && grid[currentPosX][currentPosY - 1] == NONE) {
	 currentPosY -= 1;
	 grid[currentPosX][currentPosY] = ROOM;
	 } else {
	 i--;
	 continue;
	 }
	 break;
	 case 3: //LEFT
	 if (currentPosX - 1 >= 0
	 && grid[currentPosX - 1][currentPosY] == NONE) {
	 currentPosX -= 1;
	 grid[currentPosX][currentPosY] = ROOM;
	 } else {
	 i--;
	 continue;
	 }
	 break;
	 }
	 } */
}

void Maze::makeHallways() {
	glm::ivec2 start, end;

	for (int seed = 0; seed < _seeds.size(); seed++) {

		start = _seeds[seed];
		end = _seeds[(seed + 1) % _seeds.size()];

		int dx = end.x - start.x; //distance between seeds
		std::cout << dx << std::endl;
		int dy = end.y - start.y; //distance between seeds

		//if dx or dy are > 0, we can iterate through normally. if they are <0, we have to go backwards.
		//the case where dx=0 or dy=0 does not need to be handled.
		//it also should never happen

		if (dx <= 0) {
			for (int x = start.x; x > start.x + dx; x--) {
				if (grid[x][start.y] == NONE) {
					grid[x][start.y] = HALLWAY;
				}
			}
		} else {
			for (int x = start.x; x < start.x + dx; x++) {
				if (grid[x][start.y] == NONE) {
					grid[x][start.y] = HALLWAY;
				}
			}
		}

		//we use end.x because we should already have matched x coordinates with the end
		if (dy > 0) {
			for (int y = start.y; y < start.y + dy; y++) {
				if (grid[end.x][y] == NONE) {
					grid[end.x][y] = HALLWAY;
				}
			}
		} else {
			for (int y = start.y; y > start.y + dy; y--) {
				if (grid[end.x][y] == NONE) {
					grid[end.x][y] = HALLWAY;
				}
			}
		}
	}
}
