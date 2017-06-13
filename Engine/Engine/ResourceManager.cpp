/*
 * ResourceManager.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include "ResourceManager.h"
namespace Engine {

Cache<GLTexture> ResourceManager::_textureCache;
Cache<Font> ResourceManager::_fontCache;

GLTexture ResourceManager::getTexture(const std::string& texturePath) {
	return _textureCache.get(texturePath);
}

Font ResourceManager::getFont(const std::string& fontPath) {
	return _fontCache.get(fontPath);
}

}

