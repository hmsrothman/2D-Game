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
#include "Engine/Include/Timing.h"
#include "Entity/Player.h"
#include "Dungeon/DungeonRenderer.h"
#include "Dungeon/DungeonController.h"
#include "Dungeon/Dungeon.h"
#include "Engine/Include/Font.h"

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

	Engine::Window _window; //this is the window
	GameState _gameState; //what is the game doing right now?

	//used for rendering in batches. 10/10 would recomend
	Engine::SpriteBatch _mapBatcher; //renders map. only loaded to once
	Engine::SpriteBatch _otherBatcher;//renders entities etc
	Engine::SpriteBatch _HUDBatcher;//renders HUD

	Engine::Font _font;//font for HUD

	Engine::GLSL_Program _textureShader; //shader for world, player, etc
	Engine::GLSL_Program _textShader; 	 //shader for text

	Engine::Camera2D _camera;			//camera for scene
	Engine::Camera2D _HUDCamera;		//camera for HUD

	Engine::InputManager _inputManager; //makes for smooth input

	Engine::FPSLimiter _fpsLimiter;		//monitors and caps fps

	Player _player;

	Dungeon _dungeon;
	DungeonRenderer _dungeonRenderer;
	DungeonController _dungeonController;

	void initSystems(); //init method. calls the other init method
	void initShaders(); //the other init method

	void processInput(); //does what it says on the tin

	void gameLoop();	//does what it says on the tin

	void drawGame();	//does what it says on the tin
	void drawHUD(); 	//does what it says on the tin

	float _fps;	//frames per second. computer by the limiter
	float _maxFPS;	//max allowable fps. passed to the limiter

	void ded();
};

#endif /* MAINGAME_H_ */
