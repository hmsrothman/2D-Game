/*
 * ImageLoader.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include "ImageLoader.h"
#include "picopng.h"
#include "IOManager.h"
#include "Errors.h"
#include <Gl\glew.h>
#include <Gl\gl.h>
//#include <OpenGL/gl3.h>
namespace Engine {

GLTexture ImageLoader::loadPng(const std::string& filePath) {
	GLTexture texture = { };

	std::vector<unsigned char> out;
	unsigned long width, height;
	std::vector<unsigned char> in;
	if (!IO_Manager::readFileToBuffer(filePath, in)) {
		fatalError("failed to load png to buffer");
	}

	int error = decodePNG(out, width, height, &(in[0]), in.size());

	if (error) {
		fatalError(
				"decode PNG failed with error code " + std::to_string(error));
	}

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
	GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}
}
