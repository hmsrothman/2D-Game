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


namespace Engine {

class SpriteBatch;

struct Character {
	GLuint TextureID;  //texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint Advance;    // Offset to advance to next glyph
};

struct Font {
	Font() {

	}
	Font(std::map<GLchar, Character> &chars) :
			characters(chars) {
	}
	std::map<GLchar, Character> characters;
};

class FontLoader {
public:
	static Font loadFont(const std::string& path, int size);
private:
	static FT_Library ft;
};

class FontRenderer {
public:
	static void drawText(Font& font, SpriteBatch & batcher, std::string text,
			glm::vec2 position, float scale);
};

} /* namespace Engine */

#endif /* FONT_H_ */
