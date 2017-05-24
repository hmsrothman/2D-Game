/*
 * GL_Texture.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef GLTEXTURE_H_
#define GLTEXTURE_H_
#include <Gl\glew.h>
#include <Gl\gl.h>
namespace Engine{

struct GL_Texture{
	GLuint id;
	int width;
	int height;
};


}
#endif /* GLTEXTURE_H_ */
