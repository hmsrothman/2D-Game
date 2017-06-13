/*
 * Sprite.h
 *
 *  Created on: May 16, 2017
 *      Author: Simon
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "GLTexture.h"
#include <string>
#include <OpenGL/gl3.h>

namespace Engine {

class Sprite {
public:
	Sprite();
	virtual ~Sprite();

	void draw();

	void init(float x, float y, float width, float height,
			const std::string & texturePath);
private:
	GLuint _vboID;
	GLuint _vaoID;

	int _x, _y, _width, _height;

	GL_Texture _texture;
};
}
#endif /* SPRITE_H_ */
