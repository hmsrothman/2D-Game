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

namespace Engine {

template<class T>
class ResourceLoader {
public:
	T load(const std::string & path);
};

template<>
class ResourceLoader<GL_Texture> {
public:
	GL_Texture load(const std::string & path) {
		return ImageLoader::loadPng(path);
	}
};

template<>
class ResourceLoader<Font> {
public:
	Font load(const std::string&path) {
		return Font(path);
	}
};

} /* namespace Engine */

#endif /* RESOURCELOADER_H_ */
