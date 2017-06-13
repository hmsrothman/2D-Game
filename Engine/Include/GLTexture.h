/*
 * GL_Texture.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef GLTEXTURE_H_
#define GLTEXTURE_H_
#ifdef _WIN32
#include "windows.h"
#include <Gl\glew.h>
#include <gl\GL.h>
#else
#include <OpenGl/gl3.h>
#endif
namespace Engine{

struct GLTexture{
	GLuint id;
	int width;
	int height;
};


}
#endif /* GLTEXTURE_H_ */
