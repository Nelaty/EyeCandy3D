#pragma once
#include "FontCharacter.h"

#include <gl/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

/*
* Saves all font characters of a specific font.
* Font characters will be saved on a single texture, so it can be
* used for rendering text.
*/
namespace ec
{
	class FontTextureAtlas
	{
	public:
		FontTextureAtlas(FT_Face face, int h, GLuint tUniform);
		~FontTextureAtlas();

		GLuint m_texture;
		GLuint m_textureUniform;

		/* Getter */
		int GetWidth() const;
		int GetHeight() const;
		const FontCharacter& GetChar(int index) const;
		
	private:
		/* Initialize a font texture atlas */
		void Init(FT_Face face, int h, GLuint tUniform);
	
		/* Initialization routines */
		void LoadCharacters(FT_Face face, int h);
		void CreateAtlasTexture(GLuint tUniform);
		void InitAtlasTexture(FT_Face face);

		/* Width and height of the texture */
		int m_width;
		int m_height;

		/* Characters saved in the texture */
		FontCharacter m_characters[128];

		/* Max width of a font texture atlas */
		static constexpr unsigned int s_maxWidth = 128;
	};
}