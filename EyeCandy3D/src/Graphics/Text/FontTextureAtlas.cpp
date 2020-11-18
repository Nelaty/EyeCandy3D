#include "EC3D/Graphics/Text/FontTextureAtlas.h"

#include <iostream>
#include <cassert>

namespace ec
{
	FontTextureAtlas::FontTextureAtlas(const FT_Face face,
	                                   const int h,
	                                   const GLuint tUniform)
	{
		/// \todo: height h isn't actually used.
		init(face, h, tUniform);
	}

	FontTextureAtlas::~FontTextureAtlas()
	{
		glDeleteTextures(1, &m_texture);
	}

	int FontTextureAtlas::getWidth() const
	{
		return m_textureWidth;
	}

	int FontTextureAtlas::getHeight() const
	{
		return m_textureHeight;
	}

	const FontCharacter&  FontTextureAtlas::getChar(const int index) const
	{
		assert(index < 128);
		return m_characters[index];
	}

	void FontTextureAtlas::init(const FT_Face face,
								const int h,
								const GLuint tUniform)
	{
		FT_Set_Pixel_Sizes(face, 0, h);

		loadCharacters(face, h);
		createAtlasTexture(tUniform);
		initAtlasTexture(face);

		std::cout << "Generated a " << m_textureWidth << "x " << m_textureHeight <<
			" (" << m_textureWidth * m_textureHeight / 1024 << " KiB) texture atlas.\n";
	}

	void FontTextureAtlas::loadCharacters(const FT_Face face, 
										  int h)
	{
		const auto glyphSlot = face->glyph;

		auto rowWidth = 0;
		auto rowHeight = 0;
		m_textureWidth = 0;
		m_textureHeight = 0;

		// Initialize characters with zeros
		memset(m_characters, 0, sizeof(FontCharacter));

		// Load ASCII characters
		for(auto i = 32; i < 128; i++)
		{
			if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			{
				std::cout << "Loading character %c failed\n";
				continue;
			}

			if(rowWidth + glyphSlot->bitmap.width + 1 >= s_maxWidth)
			{
				m_textureWidth = std::fmax(m_textureWidth, rowWidth);
				m_textureHeight += rowHeight;
				rowWidth = 0;
				rowHeight = 0;
			}

			rowWidth += glyphSlot->bitmap.width + 1;
			rowHeight = std::fmax(rowHeight, glyphSlot->bitmap.rows);
		}

		m_textureWidth = std::fmax(m_textureWidth, rowWidth);
		m_textureHeight += rowHeight;
	}

	void FontTextureAtlas::createAtlasTexture(const GLuint tUniform)
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_textureWidth, m_textureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Check if texture creation was successful
		const auto gl_error = glGetError();
		if(gl_error != GL_NO_ERROR)
		{
			std::cout << "Error in FontTextureAtlas::CreateAtlasTexture: " << gl_error << "\n";
		}
	}

	void FontTextureAtlas::initAtlasTexture(const FT_Face face)
	{
		const auto glyphSlot = face->glyph;

		auto offsetX = 0;
		auto offsetY = 0;
		auto rowHeight = 0;

		for(auto i = 32; i < 128; i++)
		{
			// Load character
			if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			{
				std::cout << "Loading character %c failed\n";
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
			const auto gl_error = glGetError();
			if(gl_error != GL_NO_ERROR)
			{
				std::cout << "glTexSubImage2D failed: " << gl_error << "\n";
			}

			// Save information about this character
			m_characters[i].m_advanceX = glyphSlot->advance.x >> 6;
			m_characters[i].m_advanceY = glyphSlot->advance.y >> 6;

			m_characters[i].m_bitmapWidth = glyphSlot->bitmap.width;
			m_characters[i].m_bitmapHeight = glyphSlot->bitmap.rows;

			m_characters[i].m_bitmapLeft = glyphSlot->bitmap_left;
			m_characters[i].m_bitmapTop = glyphSlot->bitmap_top;

			m_characters[i].m_uvOffsetX = offsetX / static_cast<float>(m_textureWidth);
			m_characters[i].m_uvOffsetY = offsetY / static_cast<float>(m_textureHeight);

			// Update row height and position in the row
			rowHeight = std::fmax(rowHeight, glyphSlot->bitmap.rows);
			offsetX += glyphSlot->bitmap.width + 1;
		}
	}

}
