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

class Glyph {
public:
	Glyph() {

	}
	GLuint texture;

	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;

	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture,
			float Depth, const Color& color) :
			texture(Texture), depth(Depth) {

		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	}
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

	unsigned int _numQueuedSprites;

	GlyphSortType _sortType;

	std::vector<Glyph*> _glyphPointers; //this is for sorting
	std::vector<Glyph> _glyphs;	//these are the glyphs
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
