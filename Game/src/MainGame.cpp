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

/**
 * Constructor only initializes variables
 */
MainGame::MainGame() :
		_screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _fps(
				0), _maxFPS(60), _frameTime(0) {
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {
}

/**
 * starts game
 */
void MainGame::run() {
	initSystems();
	gameLoop();
}

/**
 * initializes everything--SDL, opengl, shaders, the maze, etc
 */
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
	const float CAMERA_SPEED = 100;
	const float SCALE_SPEED = 0.05;

	//process events
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
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
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks(); //used for frame timing

		processInput();
		_camera.update();
		drawGame();
		calculateFPS();

		//print fps every 10 frames
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

		//limit fps to max; redundant with vsync which should be on, but whatever
		float frameTicks = SDL_GetTicks() - startTicks;

		if (1000 / _maxFPS > frameTicks) {
			SDL_Delay(1000 / _maxFPS - frameTicks);
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

	//the resource manager stops you from making the same texture twice
	static Engine::GL_Texture roomTexture = Engine::ResourceManager::getTexture(
			"room.png");
	static Engine::GL_Texture hallwayTexture =
			Engine::ResourceManager::getTexture("hallway.png");

	//uv coords. form (x , y , x offset , y offset)
	glm::vec4 uvRect(0, 0, 1, 1);

	//color gets multiplied by texture color
	Engine::Color color;
	//right now it's just plain white
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	//iterate through maze and queue up all of the tiles
	for (int x = 0; x < _maze.SIZE_X; x++) {
		for (int y = 0; y < _maze.SIZE_Y; y++) {
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

void MainGame::calculateFPS() { //does what it says on the tin
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

