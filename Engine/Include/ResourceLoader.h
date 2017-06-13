/*
 * ResourceLoader.h
 *
 *  Created on: Jun 1, 2017
 *      Author: Simon
 */

#ifndef RESOURCELOADER_H_
#define RESOURCELOADER_H_

#include "GLTexture.h"
#include "Font.h"
#include "ImageLoader.h"

#include "Errors.h"

namespace Engine {

template<class T>
class ResourceLoader {
public:
	T load(const std::string & path);
};

template<>
class ResourceLoader<GLTexture> {
public:
	GLTexture load(const std::string & path) {
		return ImageLoader::loadPng(path);
	}
};

template<>
class ResourceLoader<Font> {
public:
	Font load(const std::string&path) {
		return FontLoader::loadFont(path, 32);
	}
};
/*
template<>
class ResourceLoader<Mix_Chunk*> {
public:
	Mix_Chunk* load(const std::string&path) {
		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
		if (chunk) {
			return chunk;
		} else {
			fatalError(
					"Mix Chunk Loading Failed: " + std::string(Mix_GetError()));
		}
		return nullptr;
	}
};

template<>
class ResourceLoader<Mix_Music*> {
public:
	Mix_Music* load(const std::string&path) {
		Mix_Music* music = Mix_LoadMUS(path.c_str());
		if (music) {
			return music;
		} else {
			fatalError(
					"Mix Music Loading Failed: " + std::string(Mix_GetError()));
		}
		return nullptr;
	}
};
*/
}

/* namespace Engine */

#endif /* RESOURCELOADER_H_ */
