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

Dungeon::Dungeon() {
}

Dungeon::~Dungeon() {
}

void Dungeon::generate() {
	prepare();
	placeRooms();
	buildHallways();
	breakMaze();
	cullDeadEnds();
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
				mazeTiles[x][y].walls |= UP | DOWN | LEFT | RIGHT | VISITED
						| ROOM;
			}
		}
	}
	//TODO: get the rooms to have walls
}

void Dungeon::buildHallways() {
	prepare();

	//this will be in a for loop
	while (!backtrack.empty()) {
		iterate();
	}
}

void Dungeon::breakMaze() {
	//go through each tile and randomly have it connect out
	for (int x = 2; x < GRID_SIZE - 2; x++) { //outer two are excluded because they could tunnel to nothing
		for (int y = 2; y < GRID_SIZE - 2; y++) { //note that outermost is a buffer to ease maze gen
			int prb = std::rand() % mazeBreakChance;
			if (prb == 1) {
				int dir = 1 << (std::rand() % 4); //2^n?
				switch (dir) {
				case RIGHT:
					mazeTiles[x][y].walls |= RIGHT;
					mazeTiles[x + 1][y].walls |= LEFT;
					break;
				case LEFT:
					mazeTiles[x][y].walls |= LEFT;
					mazeTiles[x - 1][y].walls |= RIGHT;
					break;
				case UP:
					mazeTiles[x][y].walls |= UP;
					mazeTiles[x][y + 1].walls |= DOWN;
					break;
				case DOWN:
					mazeTiles[x][y].walls |= DOWN;
					mazeTiles[x][y - 1].walls |= UP;
					break;
				}
			}
		}
	}
	//TODO: Guarantee that every room has at least one entrance
}

void Dungeon::prepare() {
	//init array
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			mazeTiles[x][y].pos = glm::ivec2(x, y);
			if (x == 0 || y == 0 || x == GRID_SIZE - 1 || y == GRID_SIZE - 1) {
				mazeTiles[x][y].walls |= VISITED;
			}
		}
	}
	//place the rooms
	placeRooms();

	//prepare for hallwaygen
	start = &mazeTiles[1][1];
	start->walls |= VISITED | HALLWAY; //set it to visted and hallway
	backtrack.push(start);
	current = start;
}

void Dungeon::cullDeadEnds() {
	int numCulled = 1;
	while (numCulled != 0) {
		numCulled = 0;
		for (int x = 0; x < GRID_SIZE; x++) {
			for (int y = 0; y < GRID_SIZE; y++) {
				if ((mazeTiles[x][y].walls & ROOM_TYPE) == HALLWAY) {
					char rooms = mazeTiles[x][y].walls & WALLS;
					if (rooms == LEFT || rooms == RIGHT || rooms == UP
							|| rooms == DOWN) {
						++numCulled;
						mazeTiles[x][y].walls &= ~ROOM_TYPE;
						mazeTiles[x][y].walls &= ~WALLS;

						mazeTiles[x - 1][y].walls &= ~RIGHT;
						mazeTiles[x + 1][y].walls &= ~LEFT;
						mazeTiles[x][y - 1].walls &= ~UP;
						mazeTiles[x][y + 1].walls &= ~DOWN;
					}
				}
			}
		}
	}
}

void Dungeon::iterate() {
	//int x;
	//std::cin >> x;
	bool left = false, right = false, up = false, down = false;
	current->walls |= VISITED;
	if (current->pos.x + 1 < GRID_SIZE) {
		if ((mazeTiles[current->pos.x + 1][current->pos.y].walls & VISITED)
				< VISITED) {
			right = true;
		}
	}
	if (current->pos.x - 1 >= 0) {
		if ((mazeTiles[current->pos.x - 1][current->pos.y].walls & VISITED)
				< VISITED) {
			left = true;
		}
	}
	if (current->pos.y + 1 < GRID_SIZE) {
		if ((mazeTiles[current->pos.x][current->pos.y + 1].walls & VISITED)
				< VISITED) {
			up = true;
		}
	}
	if (current->pos.y - 1 >= 0) {
		if ((mazeTiles[current->pos.x][current->pos.y - 1].walls & VISITED)
				< VISITED) {
			down = true;
		}
	}

	if (up | right | left | down) {
		int dir = 1 << (std::rand() % 4); //2^n?
		switch (dir) {
		case RIGHT:
			if (right) {
				current->walls |= RIGHT; //open right wall
				current = &(mazeTiles[current->pos.x + 1][current->pos.y]);
				current->walls |= LEFT | VISITED | HALLWAY;
				backtrack.push(current);
			}
			break;
		case LEFT:
			if (left) {
				current->walls |= LEFT; //open right wall
				current = &(mazeTiles[current->pos.x - 1][current->pos.y]);
				current->walls |= RIGHT | VISITED | HALLWAY;
				backtrack.push(current);
			}
			break;
		case UP:
			if (up) {
				current->walls |= UP; //open right wall
				current = &mazeTiles[current->pos.x][current->pos.y + 1];
				current->walls |= DOWN | VISITED | HALLWAY;
				backtrack.push(current);
			}
			break;
		case DOWN:
			if (down) {
				current->walls |= DOWN; //open right wall
				current = &(mazeTiles[current->pos.x][current->pos.y - 1]);
				current->walls |= UP | VISITED | HALLWAY;
				backtrack.push(current);
			}
			break;
		}
	} else if (!backtrack.empty()) {
		current = backtrack.top();
		backtrack.pop();
	} else {
	}
}

void Dungeon::render(Engine::SpriteBatch& batcher) {
	for (int x = 0; x < GRID_SIZE; x++) {
		for (int y = 0; y < GRID_SIZE; y++) {
			char roomType = mazeTiles[x][y].walls & ROOM_TYPE;
			switch (roomType) {
			case ROOM:
				renderRoom(batcher, x, y);
				break;
			case HALLWAY:
				renderHallway(batcher, x, y);
				break;
			}
		}

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
	char walls = mazeTiles[x][y].walls & WALLS;
	switch (walls) {
	case UP | DOWN | LEFT | RIGHT: //open on all sides
		uvRect = glm::vec4(1, 1, -4, -4); //Symmetrical, so correct
		texture = roomFour.id;
		break;
	case DOWN | RIGHT | LEFT: //closed on top
		uvRect = glm::vec4(0, 0, 4, -4);
		texture = roomThreeRotated.id;
		break;
	case UP | RIGHT | LEFT: //closed on bottom
		uvRect = glm::vec4(0, 0, 4, 4);
		texture = roomThreeRotated.id;
		break;
	case DOWN | UP | LEFT: //closed on right
		uvRect = glm::vec4(0, 0, -4, 4);
		texture = roomThree.id;
		break;
	case DOWN | UP | RIGHT: //closed on left
		uvRect = glm::vec4(0, 0, 4, 4);
		texture = roomThree.id;
		break;
	default:
		texture = roomFour.id;
		uvRect = glm::vec4(0, 0, 4, 4);
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
	char walls = mazeTiles[x][y].walls & WALLS;
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
