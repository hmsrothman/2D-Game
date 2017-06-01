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
#include <OpenGL/gl3.h>
namespace Engine {

class ResourceManager {
public:
	static GL_Texture getTexture(const std::string& texturePath);
	static Font getFont(const std::string& fontPath);

private:
	static TextureCache _textureCache;
	static FontCache _fontCache;
};
}
#endif /* RESOURCEMANAGER_H_ */
