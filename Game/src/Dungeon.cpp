/*
 * Dungeon.cpp
 *
 *  Created on: May 23, 2017
 *      Author: Simon
 */

#include <Game/src/Dungeon.h>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <map>
#include <random>
#include <stack>
#include <Engine/Include/Vertex.h>
#include <Engine/Include/GLTexture.h>
#include <Engine/Include/ResourceManager.h>

Dungeon::Dungeon() :
		current(nullptr), start(nullptr) {
}

Dungeon::~Dungeon() {
}

void Dungeon::generate() {
	prepare();
	placeRooms();
	buildHallways();
	breakMaze();
	cullDeadEnds();
	fillSubTiles();
}

void Dungeon::placeRooms() {
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(ROOM_SIZE_MEAN, ROOM_SIZE_VAR);

	for (int i = 0; i < roomAttempts; i++) {

		int sizeX = distribution(generator);
		int sizeY = distribution(generator);

		int x = std::rand() % (GRID_SIZE - sizeX - 2) + 1;
		int y = std::rand() % (GRID_SIZE - sizeY - 2) + 1;

		Rectangle newRect(x, y, sizeX, sizeY);

		bool overlap = false;
		for (int rect = 0; rect < rooms.size(); rect++) {
			if (newRect.overlaps(rooms[rect])) {
				overlap = true;
			}
		}

		if (overlap) {
			continue;
		} else {

			rooms.push_back(newRect);
		}
	}

	std::cout << rooms.size() << std::endl;
	for (int i = 0; i < rooms.size(); i++) {
		std::cout << i << std::endl;
		Rectangle rect = rooms[i];
		for (int x = rect.position.x; x < rect.position.x + rect.position.z;
				x++) {
			for (int y = rect.position.y; y < rect.position.y + rect.position.w;
					y++) {
				tiles[x][y].flags |= UP | DOWN | LEFT | RIGHT | VISITED
						| NAVIGABLE;
				tiles[x][y].setTileType(ROOM);
				if (x == rect.position.x) { //if on left, close left wall
					tiles[x][y].flags &= ~LEFT;
				}
				if (x == rect.position.x + rect.position.z) { //if on right, close right wall
					tiles[x][y].flags &= ~RIGHT;
				}
				if (y == rect.position.y) { //if down, close that wall
					tiles[x][y].flags &= ~DOWN;
				}
				if (y == rect.position.y + rect.position.w) { //if up, close that wall
					tiles[x][y].flags &= ~UP;
				}
			}
		}
	}
}

void Dungeon::buildHallways() {
	//this will be in a for loop
	while (!backtrack.empty()) {
		iterateMaze();
	}
}

void Dungeon::breakMaze() {
	//go through each tile and randomly have it connect out
	for (int x = 2; x < GRID_SIZE - 2; x++) { //outer two are excluded because they could tunnel to nothing
		for (int y = 2; y < GRID_SIZE - 2; y++) { //note that outermost is a buffer to ease maze gen
			if ((tiles[x][y].flags & TILE_TYPE) == HALLWAY) {
				int prb = std::rand() % mazeBreakChance;
				if (prb == 1) {
					int dir = 1 << (std::rand() % 4); //2^n?
					tunnel(glm::ivec2(x, y), dir, 0);
					switch (dir) {
					case UP:
						if ((tiles[x][y + 1].flags & TILE_TYPE) == ROOM) {
							tiles[x][y + 1].setTileType(DOORWAY);
						}
						break;
					case DOWN:
						if ((tiles[x][y - 1].flags & TILE_TYPE) == ROOM) {
							tiles[x][y - 1].setTileType(DOORWAY);
						}
						break;
					case RIGHT:
						if ((tiles[x + 1][y].flags & TILE_TYPE) == ROOM) {
							tiles[x + 1][y].setTileType(DOORWAY);
						}
						break;
					case LEFT:
						if ((tiles[x - 1][y].flags & TILE_TYPE) == ROOM) {
							tiles[x - 1][y].setTileType(DOORWAY);
						}
						break;
					}
				}
			}
		}
	}

	//randomly give each room two entrances
	for (int i = 0; i < rooms.size(); i++) {
		bool left = false, right = false, up = false, down = false;
		if (rooms[i].position.x > 1) {
			left = true;
		}
		if (rooms[i].position.y > 1) {
			down = true;
		}
		if (rooms[i].position.x + rooms[i].position.z - 1 < GRID_SIZE - 1) {
			right = true;
		}
		if (rooms[i].position.y + rooms[i].position.w - 1 < GRID_SIZE - 1) {
			up = true;
		}
		if (right || up || down || left) {
			int entrancesMade = 0;
			while (entrancesMade < 2) {
				int dir = 1 << (std::rand() % 4);
				switch (dir) {
				case RIGHT:
					if (right) {
						int dy = std::rand() % (int) (rooms[i].position.w - 1);
						glm::ivec2 pos(
								rooms[i].position.x + rooms[i].position.z - 1,
								rooms[i].position.y + dy);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, RIGHT, 0);
						entrancesMade++;
					}
					break;
				case LEFT:
					if (left) {
						int dy = std::rand() % (int) (rooms[i].position.w - 1);
						glm::ivec2 pos(rooms[i].position.x,
								rooms[i].position.y + dy);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, LEFT, 0);
						entrancesMade++;
					}
					break;
				case DOWN:
					if (down) {
						int dx = std::rand() % (int) (rooms[i].position.z - 1);
						glm::ivec2 pos(rooms[i].position.x + dx,
								rooms[i].position.y);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, DOWN, 0);
						entrancesMade++;
					}
					break;
				case UP:
					if (up) {
						int dx = std::rand() % (int) (rooms[i].position.z - 1);
						glm::ivec2 pos(rooms[i].position.x + dx,
								rooms[i].position.y + rooms[i].position.w - 1);
						tiles[pos.x][pos.y].setTileType(DOORWAY);
						tunnel(pos, UP, 0);
						entrancesMade++;
					}
					break;
				}
			}
		}
	}

}

void Dungeon::prepare() {
//init array
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			tiles[x][y].pos = glm::ivec2(x, y);
			if (x == 0 || y == 0 || x == GRID_SIZE - 1 || y == GRID_SIZE - 1) {
				tiles[x][y].flags |= VISITED;
			}
		}
	}
	for (int x = 0; x < GRID_SIZE * 3; x++) {
		for (int y = 0; y < GRID_SIZE * 3; y++) {
			subTiles[x][y] = 0;
		}
	}

	//prepare for hallwaygen
	start = &tiles[1][1];
	start->flags |= VISITED | HALLWAY; //set it to visted and hallway
	backtrack.push(start);
	current = start;
}

void Dungeon::cullDeadEnds() {
	int numCulled = 1;
	while (numCulled != 0) {
		numCulled = 0;
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int y = 0; y < GRID_SIZE; y++) {
				if ((tiles[x][y].flags & TILE_TYPE) == HALLWAY) {
					char rooms = tiles[x][y].flags & WALLS;
					if (rooms == LEFT || rooms == RIGHT || rooms == UP
							|| rooms == DOWN) {
						++numCulled;
						tiles[x][y].flags &= ~TILE_TYPE;
						tiles[x][y].flags &= ~WALLS;
						tiles[x][y].flags &= ~NAVIGABLE;

						tiles[x - 1][y].flags &= ~RIGHT;
						tiles[x + 1][y].flags &= ~LEFT;
						tiles[x][y - 1].flags &= ~UP;
						tiles[x][y + 1].flags &= ~DOWN;
					}
				}
			}
		}
	}
}

void Dungeon::iterateMaze() {
//int x;
//std::cin >> x;
	bool left = false, right = false, up = false, down = false;
	current->flags |= VISITED;
	if (current->pos.x + 1 < GRID_SIZE) {
		if ((tiles[current->pos.x + 1][current->pos.y].flags & VISITED)
				< VISITED) {
			right = true;
		}
	}
	if (current->pos.x - 1 >= 0) {
		if ((tiles[current->pos.x - 1][current->pos.y].flags & VISITED)
				< VISITED) {
			left = true;
		}
	}
	if (current->pos.y + 1 < GRID_SIZE) {
		if ((tiles[current->pos.x][current->pos.y + 1].flags & VISITED)
				< VISITED) {
			up = true;
		}
	}
	if (current->pos.y - 1 >= 0) {
		if ((tiles[current->pos.x][current->pos.y - 1].flags & VISITED)
				< VISITED) {
			down = true;
		}
	}

	if (up | right | left | down) {
		int dir = 1 << (std::rand() % 4); //2^n?
		switch (dir) {
		case RIGHT:
			if (right) {
				tunnel(current->pos, dir, VISITED | NAVIGABLE);
				current = &(tiles[current->pos.x + 1][current->pos.y]);
				backtrack.push(current);
			}
			break;
		case LEFT:
			if (left) {
				tunnel(current->pos, dir, VISITED | NAVIGABLE);
				current = &(tiles[current->pos.x - 1][current->pos.y]);
				backtrack.push(current);
			}
			break;
		case UP:
			if (up) {
				tunnel(current->pos, dir, VISITED | NAVIGABLE);
				current = &tiles[current->pos.x][current->pos.y + 1];
				backtrack.push(current);
			}
			break;
		case DOWN:
			if (down) {
				tunnel(current->pos, dir, VISITED | NAVIGABLE);
				current = &(tiles[current->pos.x][current->pos.y - 1]);
				backtrack.push(current);
			}
			break;
		}
		current->setTileType(HALLWAY);
	} else if (!backtrack.empty()) {
		current = backtrack.top();
		backtrack.pop();
	} else {
	}
}

void Dungeon::tunnel(glm::ivec2 start, char dir, char otherFlags) {
	switch (dir) {
	case UP:
		tiles[start.x][start.y].flags |= UP | otherFlags;
		tiles[start.x][start.y + 1].flags |= DOWN | otherFlags;
		break;
	case DOWN:
		tiles[start.x][start.y].flags |= DOWN | otherFlags;
		tiles[start.x][start.y - 1].flags |= UP | otherFlags;
		break;
	case RIGHT:
		tiles[start.x][start.y].flags |= RIGHT | otherFlags;
		tiles[start.x + 1][start.y].flags |= LEFT | otherFlags;
		break;
	case LEFT:
		tiles[start.x][start.y].flags |= LEFT | otherFlags;
		tiles[start.x - 1][start.y].flags |= RIGHT | otherFlags;
		break;
	}
}

void Dungeon::fillSubTiles() {
	int sx = 0, sy = 0;
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			if (tiles[x][y].flags & NAVIGABLE) {
				sx = 3 * x;
				sy = 3 * y;
				char tileType = tiles[x][y].flags & TILE_TYPE;
				if (tileType == HALLWAY) {
					for (int dx = 0; dx < 3; dx++) {
						for (int dy = 0; dy < 3; dy++) {
							subTiles[sx + dx][sy + dy] = tileType;
							subTiles[sx + dx][sy + dy] &= ~NAVIGABLE;
						}
					}

					subTiles[sx + 1][sy + 1] |= NAVIGABLE;

					if (tiles[x][y].flags & LEFT) {
						subTiles[sx][sy + 1] |= NAVIGABLE;
					}

					if (tiles[x][y].flags & RIGHT) {
						subTiles[sx + 2][sy + 1] |= NAVIGABLE;
					}

					if (tiles[x][y].flags & UP) {
						subTiles[sx + 1][sy + 2] |= NAVIGABLE;
					}

					if (tiles[x][y].flags & DOWN) {
						subTiles[sx + 1][sy] |= NAVIGABLE;
					}
				} else if (tileType == ROOM) {
					for (int dx = 0; dx < 3; dx++) {
						for (int dy = 0; dy < 3; dy++) {
							subTiles[sx + dx][sy + dy] = tileType | NAVIGABLE;
						}
					}
				}
			}
		}
	}
}

void Dungeon::render(Engine::SpriteBatch& hallwayBatcher,
		Engine::SpriteBatch& otherBatcher) {
	//for (int x = 0; x < GRID_SIZE; x++) {
	/*for (int y = 0; y < GRID_SIZE; y++) {
	 char roomType = tiles[x][y].flags & TILE_TYPE;
	 switch (roomType) {
	 case ROOM:
	 renderRoom(batcher, x, y);
	 break;
	 case HALLWAY:
	 renderHallway(batcher, x, y);
	 break;
	 case DOOR:
	 renderDoor(batcher, x, y);
	 }
	 }*/

//	int count = 0;
	for (int x = 0; x < GRID_SIZE * 3; x++) {
		for (int y = 0; y < GRID_SIZE * 3; y++) {
			//	std::cout << x << " , " << y << std::endl;
			if (subTiles[x][y] & NAVIGABLE) {
				renderSubTile(hallwayBatcher, otherBatcher, x, y,
						subTiles[x][y] & TILE_TYPE);
				//	count++;
			}
		}
	}
//	std::cout << count << std::endl;
}

void Dungeon::renderSubTile(Engine::SpriteBatch&hallwayBatcher,
		Engine::SpriteBatch&otherBatcher, int x, int y,
		unsigned char tileType) {
	static Engine::GL_Texture doorway = Engine::ResourceManager::getTexture(
			"doorway.png");
	static Engine::GL_Texture hallway = Engine::ResourceManager::getTexture(
			"hallway.png");
	static Engine::GL_Texture room = Engine::ResourceManager::getTexture(
			"room.png");
	static Engine::GL_Texture other = Engine::ResourceManager::getTexture(
			"jimmyJump_pack/PNG/AngryCloud.png");

	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct

	unsigned int texture = 0;

	switch (tileType) {
	case ROOM:
		texture = room.id;
		otherBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	case HALLWAY:
		texture = hallway.id;
		hallwayBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	case DOORWAY:
		texture = doorway.id;
		otherBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	default:
		texture = other.id;
		otherBatcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
		break;
	}

}

void Dungeon::renderRoom(Engine::SpriteBatch &batcher, int x, int y) {
	static Engine::GL_Texture roomFour = Engine::ResourceManager::getTexture(
			"room.png");
	static Engine::GL_Texture roomThreeRotated =
			Engine::ResourceManager::getTexture("room.png");
	static Engine::GL_Texture roomThree = Engine::ResourceManager::getTexture(
			"room.png");

	int texture = 0;

	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	bool shouldRender = true;

	glm::vec4 uvRect(0, 0, 0, 0);
	char walls = tiles[x][y].flags & WALLS;
	switch (walls) {
	case UP | DOWN | LEFT | RIGHT: //open on all sides
		uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct
		texture = roomFour.id;
		break;
	case DOWN | RIGHT | LEFT: //closed on top
		uvRect = glm::vec4(0, 0, 1, -1);
		texture = roomThreeRotated.id;
		break;
	case UP | RIGHT | LEFT: //closed on bottom
		uvRect = glm::vec4(0, 0, 1, 1);
		texture = roomThreeRotated.id;
		break;
	case DOWN | UP | LEFT: //closed on right
		uvRect = glm::vec4(0, 0, -1, 1);
		texture = roomThree.id;
		break;
	case DOWN | UP | RIGHT: //closed on left
		uvRect = glm::vec4(0, 0, 1, 1);
		texture = roomThree.id;
		break;
	default:
		texture = roomFour.id;
		uvRect = glm::vec4(0, 0, 1, 1);
		//shouldRender = false;
		break;
	}
	if (shouldRender) {
		batcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
	}
}

void Dungeon::renderHallway(Engine::SpriteBatch &batcher, int x, int y) {
	static Engine::GL_Texture hallwayOne = Engine::ResourceManager::getTexture(
			"hallwayone.png");
	static Engine::GL_Texture hallwayOneRotated =
			Engine::ResourceManager::getTexture("hallwayOneRotated.png");
	static Engine::GL_Texture hallwayTwoAdjacent =
			Engine::ResourceManager::getTexture("hallwayTwoAdjacent.png");
	static Engine::GL_Texture hallwayTwoOpposite =
			Engine::ResourceManager::getTexture("hallwayTwoOpposite.png");
	static Engine::GL_Texture hallwayTwoRotated =
			Engine::ResourceManager::getTexture("hallwayTwoRotated.png");
	static Engine::GL_Texture hallwayThree =
			Engine::ResourceManager::getTexture("hallwayThree.png");
	static Engine::GL_Texture hallwayThreeRotated =
			Engine::ResourceManager::getTexture("hallwayThreeRotated.png");
	static Engine::GL_Texture hallwayFour = Engine::ResourceManager::getTexture(
			"hallwayFour.png");

	int texture = 0;

	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	bool shouldRender = true;

	glm::vec4 uvRect(0, 0, 0, 0);
	char walls = tiles[x][y].flags & WALLS;
	switch (walls) {
	case UP | DOWN | LEFT | RIGHT: //open on all sides
		uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct
		texture = hallwayFour.id;
		break;
	case DOWN | RIGHT | LEFT: //closed on top
		uvRect = glm::vec4(0, 0, 1, -1); //CORRECT
		texture = hallwayThreeRotated.id;
		break;
	case UP | RIGHT | LEFT: //closed on bottom
		uvRect = glm::vec4(0, 0, 1, 1); //CORRECT
		texture = hallwayThreeRotated.id;
		break;
	case DOWN | UP | LEFT: //closed on right
		uvRect = glm::vec4(0, 0, -1, 1); //CORRECT
		texture = hallwayThree.id;
		break;
	case DOWN | UP | RIGHT: //closed on left
		uvRect = glm::vec4(0, 0, 1, 1);
		texture = hallwayThree.id;
		break;
	case DOWN | UP: //throughfare up/down
		uvRect = glm::vec4(0, 0, 1, 1);
		texture = hallwayTwoOpposite.id; //CORRECT
		break;
	case RIGHT | LEFT: //throughfare right/left
		uvRect = glm::vec4(0, 0, 1, 1);
		texture = hallwayTwoRotated.id; //CORRECT
		break;
	case RIGHT | UP: //right/up
		uvRect = glm::vec4(0, 0, -1, -1); //CORRECT
		texture = hallwayTwoAdjacent.id;
		break;
	case RIGHT | DOWN: //right/down
		uvRect = glm::vec4(0, 0, -1, 1); //CORRECT
		texture = hallwayTwoAdjacent.id;
		break;
	case LEFT | UP: //left/up
		uvRect = glm::vec4(0, 0, 1, -1); //CORRECT
		texture = hallwayTwoAdjacent.id;
		break;
	case LEFT | DOWN: //left/down
		uvRect = glm::vec4(0, 0, 1, 1); //CORRECT
		texture = hallwayTwoAdjacent.id;
		break;
	case LEFT:
		uvRect = glm::vec4(0, 1, 1, -1); //CORRECT
		texture = hallwayOneRotated.id;
		break;
	case RIGHT:
		uvRect = glm::vec4(1, 1, -1, 1); //CORRECT
		texture = hallwayOneRotated.id;
		break;
	case UP:
		uvRect = glm::vec4(1, 1, -1, -1); //CORRECT
		texture = hallwayOne.id;
		break;
	case DOWN:
		uvRect = glm::vec4(0, 0, 1, 1); //CORRECT
		texture = hallwayOne.id;
		break;
	default:
		texture = 0;
		shouldRender = false;
		break;
	}
	if (shouldRender) {
		batcher.draw(
				glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE,
						GRID_SCALE), uvRect, texture, 0, color);
	}
}

void Dungeon::renderDoor(Engine::SpriteBatch &batcher, int x, int y) {
	static Engine::GL_Texture doorway = Engine::ResourceManager::getTexture(
			"doorway.png");
	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 uvRect = glm::vec4(1, 1, -1, -1); //Symmetrical, so correct
	batcher.draw(
			glm::vec4(x * GRID_SCALE, y * GRID_SCALE, GRID_SCALE, GRID_SCALE),
			uvRect, doorway.id, 0, color);
}
