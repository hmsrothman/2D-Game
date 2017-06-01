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
#include "Entity/Velociraptor.h"
#include "Dungeon/TileFlags.h"
#include "Items/Gun.h"
#include "Engine/Include/Font.h"
/**
 * Constructor only initializes variables
 */
MainGame::MainGame() :
		_screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY), _fps(
				0), _maxFPS(60), _player(&_inputManager, &_camera) {
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
	_camera.setScale(0.25f);
	Engine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	_fpsLimiter.setMaxFPS(_maxFPS);

	initShaders();

	_hallwayBatcher.init();
	_otherBatcher.init();
	_HUDBatcher.init();

	_font = Engine::ResourceManager::getFont("roboto/roboto-black.ttf");
//	_dungeon.prepare();
//	_dungeon.placeRooms();
	_dungeon.genMap();
	for (int i = 0; i < 400; i++) {
		_dungeon.spawnVelociraptor();
	}

	bool playerGood = false;
	while (!playerGood) {
		int x = std::rand() % _dungeon.gridSize;
		int y = std::rand() % _dungeon.gridSize;
		if (_dungeon.tileArray[_dungeon.getIndex(x, y)] & NAVIGABLE) {
			_player.setPosition(
					glm::vec2(x * _dungeon.scale, y * _dungeon.scale)); //or something. probably find a seed and put them there
			playerGood = true;
		}
	}

	_player.addGun(new Gun("Magnum", 1, 10, 0.1f, 2, 50, 100));
	_camera.lockToEntity(&_player);
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
	const float SCALE_SPEED = 0.01;

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

	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() * (1 + SCALE_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() * (1 - SCALE_SPEED));
	}
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {

		_fpsLimiter.begin();
		processInput();
		_camera.update();
		if (!_player.isded) {
			drawGame();
		} else {
			ded();
		}

		_player.update(_dungeon.bullets, _dungeon);

		_fps = _fpsLimiter.end();
		_dungeonController.update(_dungeon.velociraptors, _player, _dungeon);
		//print fps every 10 frames
		static int frameCounter = 0;
		if (frameCounter++ == 60) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

	}
}

void MainGame::ded() {
	_player.setPosition(glm::vec2(0, 0));
	_camera.setPosition(glm::vec2(0, 0));
	_camera.update();
	glClearDepth(1.0);
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static Engine::GL_Texture dedTexture = Engine::ResourceManager::getTexture(
			"endgame.png");
	_otherBatcher.begin();
	glm::vec4 destRect(-300, -300, 300, 300);
	glm::vec4 uvRect(0, 0, 1, -1);
	Engine::Color color(255, 255, 255, 255);

	_otherBatcher.draw(destRect, uvRect, dedTexture.id, 0, color);
	_otherBatcher.end();
	_otherBatcher.renderBatch();
	_window.swapBuffers();
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
	_hallwayBatcher.begin(Engine::GlyphSortType::NONE); //the hallwaybatcher will ony be used for hallways
														//therefore, we don't need to sort
	_otherBatcher.begin(Engine::GlyphSortType::TEXTURE);

	_HUDBatcher.begin(Engine::GlyphSortType::TEXTURE);

	//render dungeon
	_dungeonRenderer.render(_dungeon, _hallwayBatcher, _otherBatcher);

	//lets render the player too
	_player.render(_otherBatcher);

	_font.draw(_HUDBatcher, "01234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", _player.getPosition(), 1);
	//prep batches
	_otherBatcher.end();
	_hallwayBatcher.end();
	_HUDBatcher.end();

	//render batches
	_hallwayBatcher.renderBatch();
	_otherBatcher.renderBatch();
	_HUDBatcher.renderBatch();

	//drawHUD();

	//cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	//swap buffers
	_window.swapBuffers();
}

void MainGame::drawHUD() {
	char buffer[256];

	_HUDBatcher.begin();

	sprintf(buffer, "Blah");

	_HUDBatcher.end();
	_HUDBatcher.renderBatch();

}
