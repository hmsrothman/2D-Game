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

MainGame::MainGame() :
		_screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _time(
				0), _fps(0), _maxFPS(60), _frameTime(0) {
	_camera.init(_screenWidth, _screenHeight);

}

MainGame::~MainGame() {
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	Engine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight,
			Engine::BORDERLESS);

	initShaders();

	_spriteBatch.init();

	_maze.setSeeds();
	_maze.makeRooms();
	_maze.makeHallways();
}

void MainGame::initShaders() {
	_colorProgram.makeShaderProgram("shaders/colorShading.vert",
			"shaders/colorShading.frag");
}

void MainGame::processInput() {
	const float CAMERA_SPEED = 25;
	const float SCALE_SPEED = 0.001;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//	std::cout << event.motion.x << " " << event.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
		}
	}
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
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks();

		processInput();
		_camera.update();
		drawGame();
		calculateFPS();

		//print every 10 frames
		static int frameCounter = 0;
		if (frameCounter++ == 120) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		//check for gl error
		int error;
		while ((error = glGetError())) {
			std::cout << "ERROR " << error << std::endl;
		}

		//limit fps to max
		float frameTicks = SDL_GetTicks() - startTicks;

		if (1000 / _maxFPS > frameTicks) {
			//SDL_Delay(1000 / _maxFPS - frameTicks);
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);

	//PASS TEXTURE
	GLint textureLocation = _colorProgram.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	//PASS TIME
	_time += 0.01;
	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	//PASS ORTHOMATRIX
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//DRAW
	_spriteBatch.begin();

	//	glm::vec4 destRect(0, 0, 100, 100);
//	glm::vec4 uvRect(0, 0, 1, 1);
//	float depth = 0;
//	static Engine::GL_Texture texture = Engine::ResourceManager::getTexture(
//			"jimmyjump_pack/PNG/CharacterLeft_Jump.png");
//	Engine::Color color;
//	color.r = 255;
//	color.g = 255;
//	color.b = 255;
//	color.a = 255;
//
//	for (int i = 0; i < 1; i++) {
//		_spriteBatch.draw(destRect, uvRect, texture.id, depth, color);
//	}

	static Engine::GL_Texture roomTexture = Engine::ResourceManager::getTexture(
			"room.png");

	static Engine::GL_Texture hallwayTexture =
			Engine::ResourceManager::getTexture("hallway.png");

	glm::vec4 uvRect(0, 0, 1, 1);
	Engine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			if (_maze.grid[x][y] == ROOM) {
				glm::vec4 destRect((x - 61) * 100, (y - 61) * 100, 100, 100);
				_spriteBatch.draw(destRect, uvRect, roomTexture.id, 0, color);
			} else if (_maze.grid[x][y] == HALLWAY) {
				glm::vec4 destRect((x - 61) * 100, (y - 61) * 100, 100, 100);
				_spriteBatch.draw(destRect, uvRect, hallwayTexture.id, 0,
						color);
			}
		}
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//UNBIND EVERYTHING
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();
	_window.swapBuffers();
}

void MainGame::calculateFPS() {
	static const int NUM_SAMPLES = 100;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	previousTicks = currentTicks;

	int count = ++currentFrame < NUM_SAMPLES ? currentFrame : NUM_SAMPLES;
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 60;
	}

}

