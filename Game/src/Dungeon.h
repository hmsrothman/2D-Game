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
		return lhs.x + lhs.y < rhs.x + rhs.y;
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

	std::vector<Velociraptor> velociraptors;

	void playerWalkOnTile(glm::ivec2 tile);
	unsigned int queryTile(glm::ivec2 tile);

	int getIndex(int x, int y) const;
private:
	std::map<glm::ivec2, unsigned int, vecCompare> _playerTrail;

};

#endif /* DUNGEON_H_ */
