#pragma once
#include <gl/glew.h>

#include <map>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

/*
* Encapsulates a FreeType Lib instance and manages its initialization.
* It is used for rendering text and switching fonts.
*/
namespace ec
{
	class Shader;
	class FontTextureAtlas;

	class Freetype
	{
	public:
		explicit Freetype(Shader* shader);
		~Freetype();

		/* 
		* Render text with a specific FontTextureAtlas at a certain 
		* position with a specified relative scale
		*/
		void RenderText(const char* text, FontTextureAtlas* atlas, 
						float x, float y,
						float sx, float sy,
						const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		/* Add a new font face */
		void AddFontFace(const std::string& name, const std::string& filepath);
		
		/* Add a new texture atlas */
		void AddFontTextureAtlas(const std::string& face, unsigned int size);

		/* Try to get a existent FontTextureAtlas by name */
		FontTextureAtlas* GetFontTextureAtlas(const std::string& name);

	private:
		/* Initialization */
		void InitFreetype();

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