/*
 * Sprite.cpp
 *
 *  Created on: May 16, 2017
 *      Author: Simon
 */

#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
#include "ResourceManager.h"

namespace Engine{

Sprite::Sprite() :
		_vboID(0), _vaoID(0), _x(0), _y(0), _width(0), _height(0) {
}

Sprite::~Sprite() {
	if (_vboID) {
		glDeleteBuffers(1, &_vboID);
	}
	if (_vaoID) {
		glDeleteVertexArrays(1, &_vaoID);
	}
}

void Sprite::draw() {
	glBindVertexArray(_vaoID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,_texture.id);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Sprite::init(float x, float y, float width, float height,
		const std::string & texturePath) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = ResourceManager::getTexture(texturePath);

	if (!_vaoID) {
		glGenVertexArrays(1, &_vaoID);
	}
	glBindVertexArray(_vaoID);

	if (!_vboID) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6 * 2];

	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1, 1);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0, 1);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0, 0);

	vertexData[3].setPosition(x + width, y + height);
	vertexData[3].setUV(1, 1);

	vertexData[4].setPosition(x, y);
	vertexData[4].setUV(0, 0);

	vertexData[5].setPosition(x + width, y);
	vertexData[5].setUV(1, 0);

	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 0, 255, 255);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
	GL_STATIC_DRAW);
	//POSITION ATTRIB POINTER
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(Position) / sizeof(float), GL_FLOAT,
	GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

	//COLOR ATTRIB POINTER
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Color) / sizeof(GLubyte),
	GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));

	//UV ATTRIB POINTER
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(UV) / sizeof(float),
	GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



}
