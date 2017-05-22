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
	for (int i = 0; i < _glyphs.size(); i++) {
		delete (_glyphs[i]);
	}
	_glyphs.clear();
	_renderBatches.clear();
}

void SpriteBatch::end() {
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect,
		GLuint texture, float depth, const Color& color) {
	Glyph *newGlyph = new Glyph();
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destRect.x + destRect.z,
			destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_glyphs.push_back(newGlyph);
}

void SpriteBatch::createRenderBatches() {
	if (_glyphs.empty()) { //There is nothing to render
		return;
	}

	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	GLuint offset = 0;
	GLuint currentVertex = 0;
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	vertices[currentVertex++] = _glyphs[0]->topLeft;
	vertices[currentVertex++] = _glyphs[0]->bottomLeft;
	vertices[currentVertex++] = _glyphs[0]->bottomRight;
	vertices[currentVertex++] = _glyphs[0]->bottomRight;
	vertices[currentVertex++] = _glyphs[0]->topRight;
	vertices[currentVertex++] = _glyphs[0]->topLeft;
	offset += 6;

	for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++) {
		if (_glyphs[currentGlyph]->texture
				!= _glyphs[currentGlyph - 1]->texture) {
			_renderBatches.emplace_back(offset, 6,
					_glyphs[currentGlyph]->texture);
		} else {
			_renderBatches.back().numVertices += 6;
		}
		vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
		vertices[currentVertex++] = _glyphs[currentGlyph]->bottomLeft;
		vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
		vertices[currentVertex++] = _glyphs[currentGlyph]->bottomRight;
		vertices[currentVertex++] = _glyphs[currentGlyph]->topRight;
		vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
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
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
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
