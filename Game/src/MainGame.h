/*
 * MainGame2.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#ifndef MAINGAME_H_
#define MAINGAME_H_

<<<<<<< HEAD
//#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "Dependencies\SDL\lib\x86\SDL2.lib"
=======
#include <Engine/Include/IMainGame.h>
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
>>>>>>> refs/remotes/origin/master
#include <iostream>
#include <OpenGl/gl3.h>
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

class MainGame: public Engine::IMainGame {
public:
	MainGame();
	virtual ~MainGame();

protected:
	void initShaders();
	void onInit();
	void update();
	void draw();

	void drawGame();
	void drawHUD();
	void ded();
private:
	//used for rendering in batches. 10/10 would recomend
	Engine::SpriteBatch _mapBatcher; //renders map. only loaded to once
	Engine::SpriteBatch _otherBatcher; //renders entities etc
	Engine::SpriteBatch _HUDBatcher; //renders HUD

	Engine::Font _font; //font for HUD

<<<<<<< HEAD
	//used for rendering in batches. 10/10 would recomend
	Engine::SpriteBatch _mapBatcher; //optimization; allows to render many hallways without needing to sort
										 //necessary because there are an obscene amount of hallway tiles
	Engine::SpriteBatch _otherBatcher;//batcher for everything else. when in doubt, use this one
	Engine::SpriteBatch _HUDBatcher;

	Engine::Font _font;

	Engine::GLSL_Program _textureShader; //shader for world, player, etc
	Engine::GLSL_Program _textShader; 	 //shader for text

	Engine::Camera2D _camera;			//camera

	Engine::InputManager _inputManager; //makes for smooth input

	Engine::FPSLimiter _fpsLimiter;		//monitors and caps fps
=======
	Engine::GLSL_Program _textureShader; //shader for world, player, etc
	Engine::GLSL_Program _textShader; 	 //shader for text

	Engine::Camera2D _camera;			//camera for scene
	Engine::Camera2D _HUDCamera;		//camera for HUD
>>>>>>> refs/remotes/origin/master

	Player _player;

	Dungeon _dungeon;
	DungeonRenderer _dungeonRenderer;
	DungeonController _dungeonController;
<<<<<<< HEAD

	void initSystems(); //init method. calls the other init method
	void initShaders(); //the other init method

	void processInput(); //does what it says on the tin

	void gameLoop();	//does what it says on the tin

	void drawGame();	//does what it says on the tin
	void drawHUD(); 	//does what it says on the tin

	float _fps;	//frames per second. computer by the limiter
	float _maxFPS;	//max allowable fps. passed to the limiter

	void ded();
=======
>>>>>>> refs/remotes/origin/master
};

#endif /* MAINGAME_H_ */
