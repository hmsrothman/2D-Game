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

	unsigned char * tileArray = nullptr;
	int gridSize = 0;

	const static int GRID_SCALE = 20;

	void genMap();

	void render(Engine::SpriteBatch &hallwayBatcher,
			Engine::SpriteBatch& otherBatcher);

	std::vector<Velociraptor> velociraptors;

	void playerWalkOnTile(glm::ivec2 tile);
	unsigned int queryTile(glm::ivec2 tile);

	int getIndex(int x, int y);
private:
	void renderSubTile(Engine::SpriteBatch&hallwayBatcher,
			Engine::SpriteBatch&otherBatcher, int x, int y,
			unsigned char tileType);

	std::map<glm::ivec2, unsigned int, vecCompare> _playerTrail;

};

#endif /* DUNGEON_H_ */
