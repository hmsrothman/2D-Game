/*
 * GLSLProgram.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace Engine {
GLSL_Program::GLSL_Program() :
		_programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

}

GLSL_Program::~GLSL_Program() {
	glDeleteProgram(_programID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSL_Program::compileShaders(const std::string& vertexPath,
		const std::string& fragmentPath) {
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!_vertexShaderID) {
		fatalError("Vertex Shader Creation Failure");
	}
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!_fragmentShaderID) {
		fatalError("Fragment Shader Creation Failure");
	}

	compileShader(vertexPath, _vertexShaderID);
	compileShader(fragmentPath, _fragmentShaderID);

}

void GLSL_Program::compileShader(const std::string & filePath, GLuint id) {
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}
	std::string fileContents;
	std::string line;
	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}
	vertexFile.close();

	const char* contentsPts = fileContents.c_str();
	glShaderSource(id, 1, &contentsPts, NULL);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		fatalError("shader compilation failed" + filePath);
	}
}

void GLSL_Program::makeShaderProgram(const std::string& vertexPath,
		const std::string& fragPath) {
	compileShaders(vertexPath, fragPath);
	linkShaders();
}

void GLSL_Program::linkShaders() {
	_programID = glCreateProgram();

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint success = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, &success);

	if (!success) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &infoLog[0]);
		fatalError("shader link failed");
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSL_Program::use() {
	glUseProgram(_programID);
}

void GLSL_Program::unuse() {
	glUseProgram(0);
}

GLint GLSL_Program::getUniformLocation(const std::string& name) {
	GLint location = glGetUniformLocation(_programID, name.c_str());
	if (location == -1) {
		fatalError("uniform variable " + name + " could not be found");
	}
	return location;
}
}
