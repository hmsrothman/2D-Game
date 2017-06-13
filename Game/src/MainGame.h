/*
 * MainGame2.h
 *
 *  Created on: Jun 13, 2017
 *      Author: Simon
 */

#ifndef MAINGAME_H_
#define MAINGAME_H_

#ifdef _WIN32
#include "Dependencies\SDL\include\SDL.h"
#include "windows.h"
#include <gl\glew.h>
#include <gl\GL.h>

#else
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include <OpenGl/gl3.h>
#endif
#include <Engine/Include/IMainGame.h>
#include <iostream>

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


	Engine::GLSL_Program _textureShader; //shader for world, player, etc
	Engine::GLSL_Program _textShader; 	 //shader for text

	Engine::Camera2D _camera;			//camera

	Engine::InputManager _inputManager; //makes for smooth input

	Engine::FPSLimiter _fpsLimiter;		//monitors and caps fps

	Engine::Camera2D _HUDCamera;		//camera for HUD

	Player _player;

	Dungeon _dungeon;
	DungeonRenderer _dungeonRenderer;
	DungeonController _dungeonController;

	float _fps;	//frames per second. computer by the limiter
	float _maxFPS;	//max allowable fps. passed to the limiter
};

#endif /* MAINGAME_H_ */
