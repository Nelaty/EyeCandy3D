#include "EC3D/Core/FontTextureAtlas.h"

#include <iostream>
#include <assert.h>

namespace ec
{
	FontTextureAtlas::FontTextureAtlas(FT_Face face, int h, GLuint tUniform)
	{
		Init(face, h, tUniform);
	}

	FontTextureAtlas::~FontTextureAtlas()
	{
		glDeleteTextures(1, &m_texture);
	}

	int FontTextureAtlas::GetWidth() const
	{
		return m_width;
	}

	int FontTextureAtlas::GetHeight() const
	{
		return m_height;
	}

	const FontCharacter&  FontTextureAtlas::GetChar(int index) const
	{
		assert(index < 128);
		return m_characters[index];
	}

	void FontTextureAtlas::Init(FT_Face face, int h, GLuint tUniform)
	{
		FT_Set_Pixel_Sizes(face, 0, h);

		LoadCharacters(face, h);
		CreateAtlasTexture(tUniform);
		InitAtlasTexture(face);

		std::cout << "Generated a " << m_width << "x " << m_height <<
			" (" << m_width * m_height / 1024 << " KiB) texture atlas.\n";
	}

	void FontTextureAtlas::LoadCharacters(FT_Face face, int h)
	{
		FT_GlyphSlot glyphSlot = face->glyph;

		int roww = 0;
		int rowh = 0;
		m_width = 0;
		m_height = 0;

		// Initialize characters with zeros
		memset(m_characters, 0, sizeof(FontCharacter));

		// Load ASCII characters
		for(int i = 32; i < 128; i++)
		{
			if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			{
				std::cout << "Loading character %c failed\n", i;
				continue;
			}

			if(roww + glyphSlot->bitmap.width + 1 >= s_maxWidth)
			{
				m_width = std::fmax(m_width, roww);
				m_height += rowh;
				roww = 0;
				rowh = 0;
			}

			roww += glyphSlot->bitmap.width + 1;
			rowh = std::fmax(rowh, glyphSlot->bitmap.rows);
		}

		m_width = std::fmax(m_width, roww);
		m_height += rowh;
	}

	void FontTextureAtlas::CreateAtlasTexture(GLuint tUniform)
	{
		// Clear previous errors
		glGetError(); 

		// Generate and bind new texture
		glGenTextures(1, &m_texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glUniform1i(tUniform, 0);
		m_textureUniform = tUniform;

		// Set texture attributes
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Check if texture creation was successful
		auto gl_error = glGetError();
		if(gl_error != GL_NO_ERROR)
		{
			std::cout << "Error in FontTextureAtlas::CreateAtlasTexture: " << gl_error << "\n";
		}
	}

	void FontTextureAtlas::InitAtlasTexture(FT_Face face)
	{
		FT_GlyphSlot glyphSlot = face->glyph;

		int offsetX = 0;
		int offsetY = 0;
		int rowHeight = 0;

		for(int i = 32; i < 128; i++)
		{
			// Load character
			if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			{
				std::cout << "Loading character %c failed\n", i;
				continue;
			}

			// Start a new row if there's not enough space left in the current one
			if(offsetX + glyphSlot->bitmap.width + 1 >= s_maxWidth)
			{
				offsetY += rowHeight;
				rowHeight = 0;
				offsetX = 0;
			}

			// Add this character to the atlas texture
			glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, glyphSlot->bitmap.width, glyphSlot->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyphSlot->bitmap.buffer);

			// Check if adding it to the texture was successful
			auto gl_error = glGetError();
			if(gl_error != GL_NO_ERROR)
			{
				std::cout << "glTexSubImage2D failed: " << gl_error << "\n";
			}

			// Save information about this character
			m_characters[i].advanceX = glyphSlot->advance.x >> 6;
			m_characters[i].advanceY = glyphSlot->advance.y >> 6;

			m_characters[i].bitmapWidth = glyphSlot->bitmap.width;
			m_characters[i].bitmapHeight = glyphSlot->bitmap.rows;

			m_characters[i].bitmapLeft = glyphSlot->bitmap_left;
			m_characters[i].bitmapTop = glyphSlot->bitmap_top;

			m_characters[i].uvOffsetX = offsetX / (float)m_width;
			m_characters[i].uvOffsetY = offsetY / (float)m_height;

			// Update row height and position in the row
			rowHeight = std::fmax(rowHeight, glyphSlot->bitmap.rows);
			offsetX += glyphSlot->bitmap.width + 1;
		}
	}

}