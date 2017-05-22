/*
 * ResourceManager.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include "ResourceManager.h"
namespace Engine{

TextureCache ResourceManager::_textureCache;

GL_Texture ResourceManager::getTexture(const std::string& texturePath) {
	return _textureCache.getTexture(texturePath);
}
}
