/*
 * Player.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include <Game/src/Player.h>
#include <iostream>
#include <unordered_set>
Player::Player() :
		_position(0, 0) {
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

/*what we'll want to do here is determine which four (at most) grid cells it's in
 * and if at least one of those is not NONE
 * move the player exactly the distance between being in NONE and being in ROOM or HALLWAY
 * so it can not walk onto NONE tiles
 *
 *	ie.
 *
 *  |-----------|-----------|
 *  |	NONE	|	NONE	|
 *  |			|			|
 *  |			|			|
 *  |		|---|---|		|
 *  |_ _ _ _|XXX|XXX|_ _ _ _|
 *  |		|XXX|XXX|		|
 *  |		|---|---|		|
 *  |			|			|
 *  |	ROOM	|	ROOM	|
 *  |_ _ _ _ _ _|_ _ _ _ _ _|
 *
 *  will become
 *
 *  |-----------|-----------|
 *  |	NONE	|	NONE	|
 *  |			|			|
 *  |			|			|
 *  |			|			|
 *  |_ _ _ _|_ _|_ _|_ _ _ _|
 *  |		|XXX|XXX|		|
 *  |		|XXX|XXX|		|
 *  |		|---|---|		|
 *  |	ROOM	|	ROOM	|
 *  |_ _ _ _ _ _|_ _ _ _ _ _|
 */

