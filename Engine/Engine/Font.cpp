/*
 * Font.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: Simon
 */

#include <Font.h>
#ifdef _WIN32
#include "windows.h"
#include <gl\glew.h>
#include <gl\gL.h>
#else
#include <OpenGl/gl3.h>
#endif
#include <Errors.h>
#include <iostream>

namespace Engine {

FT_Library FontLoader::ft = nullptr;


Font FontLoader::loadFont(const std::string& path, int size) {
	FT_Face face;
	std::map<GLchar, Character> characters;

	if (!ft) { //lazy init freetype
		if (FT_Init_FreeType(&ft)) {
			fatalError("FT init failed");
		}
	}
	//load the font
	if (FT_New_Face(ft, "roboto/roboto-black.ttf", 0, &face)) {
		fatalError("font face creation failed");
	}
	FT_Set_Pixel_Sizes(face, 0, size);

	//setup character map... gonna be honest, this part is copy-pasta. blame learnopengl.com if it no work
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 127; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			fatalError("failed to load character");
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
		GL_RED,
		GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = { texture, glm::ivec2(face->glyph->bitmap.width,
				face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left,
				face->glyph->bitmap_top), (GLuint) face->glyph->advance.x };
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face (face);
	return Font(characters);
}

void FontRenderer::drawText(Font& font, SpriteBatch & batcher, std::string text,
		glm::vec2 position, float scale) {
	Color color(255, 255, 255, 255);

	for (auto c = text.begin(); c < text.end(); c++) {
		Character ch = font.characters[*c];

		float x = position.x + ch.Bearing.x * scale;
		float y = position.y - (ch.Size.y - ch.Bearing.y) * scale;
		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		batcher.draw(glm::vec4(x, y, w, h), glm::vec4(0, 1, 1, -1),
				ch.TextureID, 0, color);

		position.x += (ch.Advance >> 6) * scale;
	}
}

} /* namespace Engine */
