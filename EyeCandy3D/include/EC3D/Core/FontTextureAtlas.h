#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "FontCharacter.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ec
{
	/**
	* \brief Saves all font characters of a specific font.
	* Font characters will be saved on a single texture, so it can be
	* used for rendering text.
	*/
	class EC3D_DECLSPEC FontTextureAtlas
	{
	public:
		/**
		 * \brief FontTextureAtlas constructor.
		 * \param face The Font face.
		 * \param h Height of the font.
		 * \param tUniform Texture uniform location.
		 */
		FontTextureAtlas(FT_Face face, int h, GLuint tUniform);
		~FontTextureAtlas();

		GLuint m_texture;
		GLuint m_textureUniform;

		/**
		 * \brief Get the font texture width.
		 */
		int getWidth() const;
		/**
		 * \brief Get the font texture height.
		 */
		int getHeight() const;
		/**
		 * \brief Get a font character.
		 * \param index The position of the character.
		 */
		const FontCharacter& getChar(int index) const;
		
	private:
		/**
		 * \brief Initialize a font texture atlas.
		 */
		void init(FT_Face face, int h, GLuint tUniform);
	
		/* Initialization routines */
		/**
		 * \brief Load font characters from a font face.
		 * \param face The font face to load from.
		 * \param h The height of font.
		 */
		void loadCharacters(FT_Face face, int h);
		/**
		 * \brief Create a new texture.
		 * \param tUniform The shader uniform of the texture.
		 */
		void createAtlasTexture(GLuint tUniform);
		/**
		 * \brief Create an atlas from all previously loaded font
		 * characters.
		 * \param face The font face used for this atlas.
		 */
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