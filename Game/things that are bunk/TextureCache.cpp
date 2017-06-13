/*
 * TextureCache.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#include "TextureCache.h"
#include "ImageLoader.h"
namespace Engine {

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

GL_Texture TextureCache::getTexture(const std::string& texturePath) {
	auto iterator = _textureMap.find(texturePath); //grab texture from map

	if (iterator == _textureMap.end()) { //it wasn't in the map
		GL_Texture newTexture = ImageLoader::loadPng(texturePath);

		_textureMap.insert(make_pair(texturePath, newTexture));

		return newTexture;
	}

	return iterator->second;
}

}
