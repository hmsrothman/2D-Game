/*
 * DungeonRenderer.h
 *
 *  Created on: May 29, 2017
 *      Author: Simon
 */

#ifndef DUNGEONRENDERER_H_
#define DUNGEONRENDERER_H_

#include "Dungeon.h"
#include <Engine/Include/SpriteBatch.h>

class DungeonRenderer {
public:
	DungeonRenderer();
	virtual ~DungeonRenderer();

	void render(Dungeon& dungeon, Engine::SpriteBatch &hallwayBatcher,
			Engine::SpriteBatch& otherBatcher);
private:
	void renderSubTile(const Dungeon& dungeon, Engine::SpriteBatch&hallwayBatcher,
			Engine::SpriteBatch&otherBatcher, int x, int y,
			unsigned char tileType);

};

#endif /* DUNGEONRENDERER_H_ */
