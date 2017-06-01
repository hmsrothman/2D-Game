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

	void renderDungeon(Dungeon& dungeon, Engine::SpriteBatch &batcher);
	void renderRaptors(Dungeon& dungeon, Engine::SpriteBatch &batcher);
private:
	void renderSubTile(const Dungeon& dungeon, Engine::SpriteBatch&batcher,
			int x, int y, unsigned char tileType);

};

#endif /* DUNGEONRENDERER_H_ */
