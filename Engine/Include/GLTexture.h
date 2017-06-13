/*
 * GL_Texture.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef GLTEXTURE_H_
#define GLTEXTURE_H_

#include <OpenGL/gl3.h>
namespace Engine{

struct GLTexture{
	GLuint id;
	int width;
	int height;
};


}
#endif /* GLTEXTURE_H_ */
