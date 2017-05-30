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

class Velociraptor;

struct vecCompare: public std::binary_function<glm::ivec2, glm::ivec2, bool> {
	bool operator()(const glm::ivec2& lhs, const glm::ivec2& rhs) const {
		return lhs.x * 300 + lhs.y < (rhs.x * 300 + rhs.y); //this magic number is equal to gridSize. not sure how to pass ite
	}
};

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
private:
	std::map<int, unsigned int> _playerTrail;

};

#endif /* DUNGEON_H_ */
