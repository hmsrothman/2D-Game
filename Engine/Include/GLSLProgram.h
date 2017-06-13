/*
 * GLSLProgram.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef GLSLPROGRAM_H_
#define GLSLPROGRAM_H_

#include <string>

#ifdef _WIN32
#include "windows.h"
#include <Gl\glew.h>
#include <Gl\gl.h>
#else
#include <OpenGl/gl3.h>
#endif
namespace Engine{

class GLSL_Program {
public:
	GLSL_Program();
	virtual ~GLSL_Program();

	void use();
	void unuse();
	void makeShaderProgram(const std::string& vertexPath,
			const std::string& fragPath);

	GLint getUniformLocation(const std::string& name);

private:
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void compileShader(const std::string& filePath, GLuint id);
	void compileShaders(const std::string& vertexPath,
			const std::string& fragPath);
	void linkShaders();
};

}
#endif /* GLSLPROGRAM_H_ */
