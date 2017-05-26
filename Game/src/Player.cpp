/*
 * Player.cpp
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#include "Player.h"
#include <iostream>
#include <unordered_set>
#include <Engine/Include/ResourceManager.h>
#include <Engine/Include/Vertex.h>
#include "Dungeon.h"

Player::Player() :
		_position(0, 0) {

}

Player::~Player() {
}

void Player::render(Engine::SpriteBatch batcher) { //this doesn't work for some reason
	static Engine::GL_Texture playerTexture =
			Engine::ResourceManager::getTexture(
					"jimmyjump_pack/PNG/AngryCloud.png");
	glm::vec4 uvRect(1, 1, -1, -1);
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 destRect(_position.x, _position.y, PLAYER_SIZE, PLAYER_SIZE);
	std::cout << "draw" << std::endl;
	batcher.draw(destRect, uvRect, playerTexture.id, 0, color);
}

void Player::move(glm::vec2 translation, Dungeon& map) {
	//make a Rectangle which is player sprite
	//use Rectangle and some Rectangles representing map tiles to check which tiles player is on
	//make Rectangle(s) which is the wall portion(s) of map tile(s) the player is on
	//if the player overlaps this (these) rectangle(s), correct accordingly
	//this will work IFF player speed << path width
	//if player speed !<< path width gameplay would be fucked anyway so i think we're good
	int x = _position.x / map.GRID_SCALE;
	int y = _position.y / map.GRID_SCALE;

	_position += translation;
}
