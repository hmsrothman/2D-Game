/*
 * MainGame.h
 *
 *  Created on: May 16, 2017
 *      Author: Simon
 */

#ifndef MAINGAME_H_
#define MAINGAME_H_

#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <iostream>
#include <OpenGl/gl3.h>
#include "Engine/Include/Sprite.h"
#include "Engine/Include/GLSLProgram.h"
#include "Engine/Include/GLTexture.h"
#include "Engine/Include/Window.h"
#include "Engine/Include/Camera2D.h"
#include "Engine/Include/SpriteBatch.h"
#include "Engine/Include/InputManager.h"
#include "Maze.h"

class MainGame {
	enum GameState {
		PLAY, EXIT
	};
public:
	MainGame();
	virtual ~MainGame();

	void run();
private:
	int _screenWidth;
	int _screenHeight;

	Engine::Window _window;
	GameState _gameState;

	Engine::SpriteBatch _spriteBatch;

	Engine::GLSL_Program _colorProgram;

	Engine::Camera2D _camera;

	Engine::InputManager _inputManager;

	Maze _maze;

	void initSystems();
	void initShaders();
	void processInput();
	void gameLoop();
	void drawGame();
	void calculateFPS();

	float _time;

	float _fps;
	float _frameTime;
	float _maxFPS;
};

#endif /* MAINGAME_H_ */
