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
<<<<<<< HEAD
#include <Gl\glew.h>
#include <Gl\gl.h>
=======
#include <OpenGL/gl3.h>
#include "Font.h"

>>>>>>> refs/remotes/origin/master
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
