/*
 * Player.h
 *
 *  Created on: May 22, 2017
 *      Author: Simon
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <glm/glm.hpp>
#include "GameEntity.h"
#include "../Dungeon/Dungeon.h"
#include "../Items/Inventory.h"
#include "../Items/Gun.h"
#include <Engine/Include/InputManager.h>
#include <Engine/Include/Camera2D.h>

class Player: public GameEntity {
public:
	Player(Engine::InputManager* inputManager, Engine::Camera2D* camera);
	Player() : GameEntity(10){

	}

	void init(Engine::InputManager* inputManager, Engine::Camera2D* camera);
	virtual ~Player();

	void render(Engine::SpriteBatch& batcher) const; // this appears to not work
	void move(glm::vec2 displacement, Dungeon& map);
	void kill();

	void update(std::vector<Bullet>& bullets, Dungeon& map);

	bool isded = false;

	void addGun(Gun* gun);

	int speed = 2;
private:
	std::vector<Gun*> _guns;
	int _currentGun = -1;
	Engine::InputManager* _inputManager;
	Engine::Camera2D* _camera;
};

#endif /* PLAYER_H_ */
