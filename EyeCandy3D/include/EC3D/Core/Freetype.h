#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include <map>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ec
{
	class Shader;
	class FontTextureAtlas;

	/*
	 * \brief Encapsulates a FreeType Lib instance and manages its 
	 * initialization. It is used for rendering text and switching fonts.
	 */
	class EC3D_DECLSPEC Freetype
	{
	public:
		/**
		 * \brief Freetype constructor.
		 * \param shader The text shader used for rendering text.
		 */
		explicit Freetype(Shader* shader);
		~Freetype();

		/**
		* \brief Render text with a specific FontTextureAtlas at a given 
		* position with a given relative scale.
		* \param text The text to draw.
		* \param atlas The font used for drawing
		* \param x X coordinate in screen coordinates.
		* \param y Y coordinate in screen coordinate.
		* \param sx 
		* \param sy
		* \param color The color of the text.
		*/
		void renderText(const char* text, FontTextureAtlas* atlas, 
						float x, float y,
						float sx, float sy,
						const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) const;

		/**
		 * \brief Add a new font face.
		 * \param name The name of the font.
		 * \param filepath The path to the font.
		 */
		void addFontFace(const std::string& name, const std::string& filepath);
		
		/**
		 * \brief Add a new texture atlas.
		 * \param face The font to use.
		 * \param size The size of characters.
		 */
		void addFontTextureAtlas(const std::string& face, unsigned int size);

		/**
		 * \brief Try to get a existent FontTextureAtlas by name.
		 * \param name The name of the atlas.
		 * \return The atlas if it was found, nullptr otherwise.
		 */
		FontTextureAtlas* getFontTextureAtlas(const std::string& name);

	private:
		/**
		 * \brief Initialize th freetype library.
		 */
		void initFreetype();

		/**
		 * \brief Shader used for rendering text.
		 */
		Shader* m_textShader;

		/* Vertex data */
		GLuint m_vbo;
		GLuint m_vao;

		/* Uniform location */
		GLuint m_uvPosLocation;
		GLuint m_colorLocation;
		GLuint m_textureLocation;

		/* FTLibrary, FTFaces and atlases */
		FT_Library m_ftLib;
		std::map<std::string, FT_Face> m_fontFaces;
		std::map<std::string, std::unique_ptr<FontTextureAtlas>> m_fontTextureAtlases;
	};
}