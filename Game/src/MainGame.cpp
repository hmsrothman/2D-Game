/*
 * MainGame.cpp
 *
 *  Created on: May 16, 2017
 *      Author: Simon
 */

#include "MainGame.h"
#include "Engine/Include/Errors.h"
#include "Engine/Include/Engine.h"
#include "Engine/Include/ResourceManager.h"
#include "Engine/Include/Vertex.h"
#include <iostream>
/**
 * Constructor only initializes variables
 */
MainGame::MainGame() :
		_screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _fps(
				0), _maxFPS(60) {
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {
}

/**
 * starts game
 */
void MainGame::run() {
	std::cout << "wtf" << std::endl;
	initSystems();
	std::cout << "wtf" << std::endl;
	gameLoop();
}

/**
 * initializes everything--SDL, opengl, shaders, the maze, etc
 */
void MainGame::initSystems() {

	Engine::init();
	_window.create("Game Engine", _screenWidth, _screenHeight, 0);


	_fpsLimiter.setMaxFPS(_maxFPS);

	initShaders();

	_spriteBatch.init();

	_dungeon.generate();

	_player.setPosition(glm::vec2(0, 0)); //or something. probably find a seed and put them there
}

/**
 * does what it says on the tin
 */
void MainGame::initShaders() {
	_colorProgram.makeShaderProgram("shaders/colorShading.vert",
			"shaders/colorShading.frag");
}

/**
 * does what it says on the tin
 */
void MainGame::processInput() {
	const float CAMERA_SPEED = 5;
	const float SCALE_SPEED = 0.01;

	const float PLAYER_SPEED = 10;

	//process events
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		}
	}

	//act on keyboard events
	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(
				_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(
				_camera.getPosition() + glm::vec2(0, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() * (SCALE_SPEED + 1));
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() * (1 - SCALE_SPEED));
	}

	//we'll probably bind the camera to the player later, but for now arrow keys move the player
	if (_inputManager.isKeyPressed(SDLK_UP)) {
		_player.setPosition(_player.getPosition() + glm::vec2(0, PLAYER_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_DOWN)) {
		_player.setPosition(
				_player.getPosition() + glm::vec2(0, -PLAYER_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_LEFT)) {
		_player.setPosition(
				_player.getPosition() + glm::vec2(-PLAYER_SPEED, 0));
	}
	if (_inputManager.isKeyPressed(SDLK_RIGHT)) {
		_player.setPosition(_player.getPosition() + glm::vec2(PLAYER_SPEED, 0));
	}

	//mouse
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 coords = _inputManager.getMouseCoords();
		coords = _camera.convertScreenToWorld(coords);
		std::cout << coords.x << " , " << coords.y << std::endl;
	}
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		_fpsLimiter.begin();
		processInput();
		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();

		//_dungeon.iterate();

		//print fps every 10 frames
		static int frameCounter = 0;
		if (frameCounter++ == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use shader
	_colorProgram.use();

	//turn on textures
	glActiveTexture(GL_TEXTURE0);

	//pass texture
	GLint textureLocation = _colorProgram.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	//pass matrix
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//being draw call
	_spriteBatch.begin();

	static Engine::GL_Texture playerTexture =
			Engine::ResourceManager::getTexture(
					"jimmyjump_pack/PNG/AngryCloud.png");

	//hallwayThree = playerTexture;
	//hallwayFour = playerTexture;

	//uv coords. form (x , y , x offset , y offset)
	//it's kinda weird to componsate for the fact that opengl's texture coords are upside-down
	glm::vec4 uvRect(1, 1, -1, -1);

	//color gets multiplied by texture color
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	//render dungeon
	_dungeon.render(_spriteBatch);

	//lets render the player too
	glm::vec2 playerPos = _player.getPosition();
	glm::vec4 destRect(playerPos.x, playerPos.y, _player.PLAYER_SIZE,
			_player.PLAYER_SIZE);
	_spriteBatch.draw(destRect, uvRect, playerTexture.id, 0, color);

	//prep batches
	_spriteBatch.end();

	//render batches
	_spriteBatch.renderBatch();

	//cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	//swap buffers
	_window.swapBuffers();
}
