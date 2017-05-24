/*
 * ResourceManager.h
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "TextureCache.h"
#include <string>
#include "GLTexture.h"
#include <Gl\glew.h>
#include <Gl\gl.h>
namespace Engine {

class ResourceManager {
public:
	static GL_Texture getTexture(const std::string& texturePath);

private:
	static TextureCache _textureCache;
};
}
#endif /* RESOURCEMANAGER_H_ */
