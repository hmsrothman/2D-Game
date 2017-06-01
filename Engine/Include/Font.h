/*
 * Font.h
 *
 *  Created on: Jun 1, 2017
 *      Author: Simon
 */

#ifndef FONT_H_
#define FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>
#include <map>
#include "SpriteBatch.h"
#include "Vertex.h"

namespace Engine {

struct Character {
	GLuint TextureID;  //texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint Advance;    // Offset to advance to next glyph
};

class Font {
public:
	Font() {

	}
	static FT_Library ft;
	Font(const std::string& path);
	void load(const std::string& path, int size);
	void draw(SpriteBatch & batcher, std::string text, glm::vec2 position,
			float scale);
	virtual ~Font();
private:
	FT_Face _face;
	std::map<GLchar, Character> _characters;
};

} /* namespace Engine */

#endif /* FONT_H_ */
