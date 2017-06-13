/*
 * ResourceManager.h
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Cache.h"
#include <string>
#include "GLTexture.h"
#include <OpenGL/gl3.h>

namespace Engine {

struct Font;

class ResourceManager {
public:
	static GL_Texture getTexture(const std::string& texturePath);
	static Font getFont(const std::string& fontPath);

private:
	static Cache<GL_Texture> _textureCache;
	static Cache<Font> _fontCache;
};
}
#endif /* RESOURCEMANAGER_H_ */
