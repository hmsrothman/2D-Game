/*
 * SpriteBatch.h
 *
 *  Created on: May 21, 2017
 *      Author: Simon
 */

#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include <Gl\glew.h>
#include <Gl\gl.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace Engine {

enum GlyphSortType {
	NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE
};

struct Glyph {
	GLuint texture;

	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
			offset(Offset), numVertices(NumVertices), texture(Texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch {
public:
	SpriteBatch();
	virtual ~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4& desinationRectangle, const glm::vec4& uvRect,
			GLuint texture, float depth, const Color& color);

	void renderBatch();
private:
	GLuint _vboID;
	GLuint _vaoID;

	GlyphSortType _sortType;

	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatches;

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph*a, Glyph*b);
	static bool compareBackToFront(Glyph*a, Glyph*b);
	static bool compareTexture(Glyph*a, Glyph*b);

};

} /* namespace Engine */

#endif /* SPRITEBATCH_H_ */
