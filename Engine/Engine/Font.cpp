/*
 * Font.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: Simon
 */

#include <Engine/Engine/Font.h>
#include <OpenGL/gl3.h>

namespace Engine {

FT_Library Font::ft = nullptr;

Font::Font() {

}

Font::~Font() {
}

void Font::load(const std::string& path, int size) {
	if (!ft) { //lazy init freetype
		FT_Init_FreeType(&ft);
	}
	//load the font
	FT_New_Face(ft, path.c_str(), 0, &_face);
	FT_Set_Pixel_Sizes(_face, 0, size);

	//setup character map... gonna be honest, this part is copy-pasta. blame learnopengl.com if it no work
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(_face, c, FT_LOAD_RENDER)) {
			fatalError("failed to load character: " + c);
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RED, _face->glyph->bitmap.width, _face->glyph->bitmap.rows, 0,
		GL_RED,
		GL_UNSIGNED_BYTE, _face->glyph->bitmap.buffer);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = { texture, glm::ivec2(_face->glyph->bitmap.width,
				_face->glyph->bitmap.rows), glm::ivec2(
				_face->glyph->bitmap_left, _face->glyph->bitmap_top),
				_face->glyph->advance.x };
		_characters.insert(std::pair<GLchar, Character>(c, character));

		FT_Done_Face (face);
	}

}

} /* namespace Engine */
