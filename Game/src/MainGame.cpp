/*
 * MainGame2.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#include <Game/src/MainGame.h>
#include "Engine/Include/Errors.h"
#include "Engine/Include/Engine.h"
#include "Engine/Include/ResourceManager.h"
#include "Engine/Include/Vertex.h"
#include <iostream>
#include "Entity/Velociraptor.h"
#include "Dungeon/TileFlags.h"
#include "Items/Gun.h"
#include "Engine/Include/Font.h"

MainGame::MainGame() {
	// TODO Auto-generated constructor stub

}

MainGame::~MainGame() {
	// TODO Auto-generated destructor stub
}

void MainGame::initShaders() {
	_textureShader.makeShaderProgram("shaders/colorShading.vert",
			"shaders/colorShading.frag");
	_textShader.makeShaderProgram("shaders/colorShading.vert",
			"shaders/text.frag");
}

void MainGame::onInit() {
	//init cameras
	_camera.init(_screenWidth, _screenHeight);
	_HUDCamera.init(_screenWidth, _screenHeight);
	_camera.setScale(0.25f);

	//setup sprite batchers
	_mapBatcher.init();
	_otherBatcher.init();
	_HUDBatcher.init();

	//setup font
	_font = Engine::ResourceManager::getFont(
			"Resources/roboto/roboto-black.ttf");

	//setup sprite batchers
	_mapBatcher.init();
	_otherBatcher.init();
	_HUDBatcher.init();

	//setup font
	_font = Engine::ResourceManager::getFont("roboto/roboto-black.ttf");

	_dungeon.genMap();
	for (int i = 0; i < 400; i++) {
		_dungeon.spawnVelociraptor();
	}

	//build the map batcher only once
	_mapBatcher.begin();
	_dungeonRenderer.renderDungeon(_dungeon, _mapBatcher);
	_mapBatcher.end();

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

	_player.addGun(new Gun("Magnum", 1, 10, 0.1f, 2, 50, 100000));
	_camera.lockToEntity(&_player);


}

void MainGame::update() {
	const float SCALE_SPEED = 0.01;
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() * (1 + SCALE_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() * (1 - SCALE_SPEED));
	}

	_player.update(_dungeon.bullets, _dungeon);
	_dungeonController.update(_dungeon.velociraptors, _player, _dungeon);
	_camera.update();
	_HUDCamera.update();
}

void MainGame::draw() {
	if (_player.health > 0) {
		drawGame();
		drawHUD();
	} else {
		ded();
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use shader
	_textureShader.use();

	//turn on textures
	glActiveTexture(GL_TEXTURE0);

	//pass texture
	GLint textureLocation = _textureShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	//pass matrix
	GLuint pLocation = _textureShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//being draw call
	_otherBatcher.begin(Engine::GlyphSortType::TEXTURE);

	//render player
	_player.render(_otherBatcher);

	//render raptors and bullets and stuff
	_dungeonRenderer.renderRaptors(_dungeon, _otherBatcher);

	//prep batcher
	_otherBatcher.end();

	//render batches (including map)
	_mapBatcher.renderBatch();
	_otherBatcher.renderBatch();

	//cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	_textureShader.unuse();
}

void MainGame::drawHUD() {
	static char charBuffer[256];

	//use shader
	_textShader.use();

	//turn on textures
	glActiveTexture(GL_TEXTURE0);

	//pass texture
	GLint textureLocation = _textureShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	//pass matrix
	GLuint pLocation = _textureShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = _HUDCamera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_HUDBatcher.begin();

	snprintf(charBuffer, 256, "Your health is: %.1f", _player.health);

	Engine::FontRenderer::drawText(_font, _HUDBatcher, charBuffer,
			glm::vec2(0, 0), 1);

	_HUDBatcher.end();
	_HUDBatcher.renderBatch();

	//cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	_textShader.unuse();
}

void MainGame::ded() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use shader
	_textureShader.use();

	//turn on textures
	glActiveTexture(GL_TEXTURE0);

	//pass texture
	GLint textureLocation = _textureShader.getUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	//pass matrix
	GLuint pLocation = _textureShader.getUniformLocation("P");
	glm::mat4 cameraMatrix = _HUDCamera.getMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//_player.setPosition(glm::vec2(0, 0));
	//_camera.setPosition(glm::vec2(0, 0));
	//_camera.update();
	static Engine::GLTexture dedTexture = Engine::ResourceManager::getTexture(
			"endgame.png");
	_otherBatcher.begin();
	glm::vec4 destRect(-300, -300, 300, 300);
	glm::vec4 uvRect(0, 0, 1, -1);
	Engine::Color color(255, 255, 255, 255);

	_otherBatcher.draw(destRect, uvRect, dedTexture.id, 0, color);
	_otherBatcher.end();
	_otherBatcher.renderBatch();
}
