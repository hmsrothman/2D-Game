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
#ifdef _WIN32
#include "windows.h"
#include <Gl\glew.h>
#include <gl\GL.h>
#else
#include <OpenGl/gl3.h>
#endif
#include "Font.h"

namespace Engine {

class ResourceManager {
public:
	static GLTexture getTexture(const std::string& texturePath);
	static Font getFont(const std::string& fontPath);

private:
	static Cache<GLTexture> _textureCache;
	static Cache<Font> _fontCache;
};
}
#endif /* RESOURCEMANAGER_H_ */
