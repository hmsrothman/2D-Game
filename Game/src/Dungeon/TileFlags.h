/*
 * TileFlags.h
 *
 *  Created on: May 29, 2017
 *      Author: Simon
 */

#ifndef TILEFLAGS_H_
#define TILEFLAGS_H_

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

#endif /* TILEFLAGS_H_ */
