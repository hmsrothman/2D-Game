/*
 * SpriteBatch.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Simon
 */

#include <SpriteBatch.h>
#include <algorithm>

namespace Engine {

SpriteBatch::SpriteBatch() :
		_vboID(0), _vaoID(0) {
	// TODO Auto-generated constructor stub

}

SpriteBatch::~SpriteBatch() {
	// TODO Auto-generated destructor stub
}

void SpriteBatch::init() {
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType) {
	_sortType = sortType;
	_glyphs.clear();
	_renderBatches.clear();
}

void SpriteBatch::end() {
	_glyphPointers.resize(_glyphs.size());
	for (int i = 0; i < _glyphs.size(); i++) {
		_glyphPointers[i] = &(_glyphs[i]);
	}
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect,
		GLuint texture, float depth, const Color& color) {

	_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::createRenderBatches() {
	if (_glyphPointers.empty()) { //There is nothing to render
		return;
	}

	std::vector<Vertex> vertices;
	vertices.resize(_glyphPointers.size() * 6);

	GLuint offset = 0;
	GLuint currentVertex = 0;
	_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
	vertices[currentVertex++] = _glyphPointers[0]->topLeft;
	vertices[currentVertex++] = _glyphPointers[0]->bottomLeft;
	vertices[currentVertex++] = _glyphPointers[0]->bottomRight;
	vertices[currentVertex++] = _glyphPointers[0]->bottomRight;
	vertices[currentVertex++] = _glyphPointers[0]->topRight;
	vertices[currentVertex++] = _glyphPointers[0]->topLeft;
	offset += 6;

	for (int currentGlyph = 1; currentGlyph < _glyphPointers.size();
			currentGlyph++) {
		if (_glyphPointers[currentGlyph]->texture
				!= _glyphPointers[currentGlyph - 1]->texture) {
			_renderBatches.emplace_back(offset, 6,
					_glyphPointers[currentGlyph]->texture);
		} else {
			_renderBatches.back().numVertices += 6;
		}
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->topLeft;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomLeft;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->bottomRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->topRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), nullptr, //ORPHAN BUFFER
			GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), //UPLOAD NEW DATA
	vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray() {
	if (!_vboID) {
		glGenVertexArrays(1, &_vaoID);
	}
	glBindVertexArray(_vaoID);

	if (!_vboID) {
		glGenBuffers(1, &_vboID);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

//Enable Vertex Attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

//Setup Vertex Attrib Pointers
	glVertexAttribPointer(0, sizeof(Position) / sizeof(float), GL_FLOAT,
	GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
	glVertexAttribPointer(1, sizeof(Color) / sizeof(GLubyte),
	GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) offsetof(Vertex, color));
	glVertexAttribPointer(2, sizeof(UV) / sizeof(float),
	GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::renderBatch() {
	glBindVertexArray(_vaoID);
	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		//	std::cout << _renderBatches[i].texture;
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset,
				_renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs() {
	switch (_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
				compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph*a, Glyph*b) {
	return a->depth < b->depth;
}

bool SpriteBatch::compareBackToFront(Glyph*a, Glyph*b) {
	return a->depth > b->depth;
}

bool SpriteBatch::compareTexture(Glyph*a, Glyph*b) {
	return a->texture < b->depth;
}

} /* namespace Engine */
