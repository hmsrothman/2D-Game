/*
 * GameEntity.cpp
 *
 *  Created on: May 26, 2017
 *      Author: Simon
 */

#include "GameEntity.h"
#include "TileFlags.h"

void GameEntity::move(glm::vec2 translation, Dungeon& map) {
	glm::vec2 pos = _position;
	int currentX = pos.x / map.scale;
	int currentY = pos.y / map.scale;

	glm::vec2 destination = pos + translation;
	int destinationX = destination.x / map.scale;
	int destinationY = destination.y / map.scale;

	bool botLeftCantMove = (map.tileArray[map.getIndex(currentX, currentY)]
			& NAVIGABLE)
			&& !((map.tileArray[map.getIndex(destinationX, destinationY)]
					& NAVIGABLE));

	pos += glm::vec2(renderSize, 0);

	currentX = pos.x / map.scale;
	currentY = pos.y / map.scale;

	destination = pos + translation;
	destinationX = destination.x / map.scale;
	destinationY = destination.y / map.scale;

	bool botRightCantMove = (map.tileArray[map.getIndex(currentX, currentY)]
			& NAVIGABLE)
			&& !((map.tileArray[map.getIndex(destinationX, destinationY)]
					& NAVIGABLE));

	pos += glm::vec2(0, renderSize);

	currentX = pos.x / map.scale;
	currentY = pos.y / map.scale;

	destination = pos + translation;
	destinationX = destination.x / map.scale;
	destinationY = destination.y / map.scale;

	bool topRightCantMove = (map.tileArray[map.getIndex(currentX, currentY)]
			& NAVIGABLE)
			&& !((map.tileArray[map.getIndex(destinationX, destinationY)]
					& NAVIGABLE));

	pos -= glm::vec2(renderSize, 0);

	currentX = pos.x / map.scale;
	currentY = pos.y / map.scale;

	destination = pos + translation;
	destinationX = destination.x / map.scale;
	destinationY = destination.y / map.scale;

	bool topLeftCantMove = (map.tileArray[map.getIndex(currentX, currentY)]
			& NAVIGABLE)
			&& !((map.tileArray[map.getIndex(destinationX, destinationY)]
					& NAVIGABLE));

	if (topLeftCantMove || topRightCantMove || botLeftCantMove
			|| botRightCantMove) {
		//dont move  because we are trying to go from somewhere we can to somewhere we can't
	} else {
		_position += translation;
	}
}
