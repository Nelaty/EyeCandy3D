#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "FontCharacter.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ec
{
	/**
	* Saves all font characters of a specific font.
	* Font characters will be saved on a single texture, so it can be
	* used for rendering text.
	*/
	class EC3D_DECLSPEC FontTextureAtlas
	{
	public:
		FontTextureAtlas(FT_Face face, int h, GLuint tUniform);
		~FontTextureAtlas();

		GLuint m_texture;
		GLuint m_textureUniform;

		/* Getter */
		int getWidth() const;
		int getHeight() const;
		const FontCharacter& getChar(int index) const;
		
	private:
		/* Initialize a font texture atlas */
		void init(FT_Face face, int h, GLuint tUniform);
	
		/* Initialization routines */
		void loadCharacters(FT_Face face, int h);
		void createAtlasTexture(GLuint tUniform);
		void initAtlasTexture(FT_Face face);

		/* Width and height of the texture */
		int m_width;
		int m_height;

		/* Characters saved in the texture */
		FontCharacter m_characters[128];

		/* Max width of a font texture atlas */
		static constexpr unsigned int s_maxWidth = 128;
	};
}