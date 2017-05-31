/*
 * Dungeon.h
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <vector>
#include <map>
#include <Engine/Include/SpriteBatch.h>
#include "../Items/Bullet.h"

class Velociraptor;

class Dungeon {
public:
	Dungeon();
	virtual ~Dungeon();

	int scale = 20;

	unsigned char * tileArray = nullptr;
	int gridSize = 0;

	void genMap();
	void spawnVelociraptor();

	std::vector<Velociraptor> velociraptors;

	void playerWalkOnTile(glm::ivec2 tile);
	unsigned int queryTile(glm::ivec2 tile);

	int getIndex(int x, int y) const;

	std::vector<Bullet> bullets;
private:
	std::map<int, unsigned int> _playerTrail;
};

#endif /* DUNGEON_H_ */
