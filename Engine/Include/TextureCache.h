/*
 * TextureCache.h
 *
 *  Created on: May 20, 2017
 *      Author: Simon
 */

#ifndef TEXTURECACHE_H_
#define TEXTURECACHE_H_

#include "GLTexture.h"
#include <string>
#include <map>
namespace Engine {

class TextureCache {
public:
	TextureCache();
	~TextureCache();

	GL_Texture getTexture(const std::string& texturePath);

private:
	std::map<std::string, GL_Texture> _textureMap;
};
}
#endif /* TEXTURECACHE_H_ */
