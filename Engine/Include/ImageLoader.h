/*
 * ImageLoader.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include "GLTexture.h"
#include <string>
namespace Engine{

class ImageLoader {
public:
	static GLTexture loadPng(const std::string& filepath);
};
}
#endif /* IMAGELOADER_H_ */
