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
#include "Dungeon.h"
#include "Player.h"

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
	Engine::SpriteBatch _hallwayBatcher; //optimization; allows to render many hallways without needing to sort
										 //necessary because there are an obscene amount of hallway tiles
	Engine::SpriteBatch _otherBatcher;//batcher for everything else. when in doubt, use this one
	Engine::GLSL_Program _colorProgram; //shader program
	Engine::Camera2D _camera;			//camera
	Engine::InputManager _inputManager; //makes for smooth input
	Engine::FPSLimiter _fpsLimiter;		//monitors and caps fps

	Player _player;
	Dungeon _dungeon;

	void initSystems(); //init method. calls the other init method
	void initShaders(); //the other init method
	void processInput(); //does what it says on the tin
	void gameLoop();	//does what it says on the tin
	void drawGame();	//does what it says on the tin

	float _fps;	//frames per second. computer by the limiter
	float _maxFPS;	//max allowable fps. passed to the limiter
};

#endif /* MAINGAME_H_ */
