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
		*/
		void renderText(const char* text, FontTextureAtlas* atlas, 
						float x, float y,
						float sx, float sy,
						const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) const;

		/* Add a new font face */
		void addFontFace(const std::string& name, const std::string& filepath);
		
		/* Add a new texture atlas */
		void addFontTextureAtlas(const std::string& face, unsigned int size);

		/* Try to get a existent FontTextureAtlas by name */
		FontTextureAtlas* getFontTextureAtlas(const std::string& name);

	private:
		/* Initialization */
		void initFreetype();

		/* Shader used for rendering text */
		Shader* m_textShader;

		/* Vertex data */
		GLuint m_VBO;
		GLuint m_VAO;

		/* Uniform location */
		GLuint m_posUV;
		GLuint m_colorIN;
		GLuint m_texture;

		/* FTLibrary, FTFaces and atlases */
		FT_Library m_ftLib;
		std::map<std::string, FT_Face> m_fontFaces;
		std::map<std::string, std::unique_ptr<FontTextureAtlas>> m_fontTextureAtlases;
	};
}