/*
 * ImageLoader.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <string>
namespace Engine{

struct GL_Texture;

class ImageLoader {
public:
	static GL_Texture loadPng(const std::string& filepath);
};
}
#endif /* IMAGELOADER_H_ */
