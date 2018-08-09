#include "EC3D/Core/Freetype.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/FontTextureAtlas.h"

#include <iostream>
#include <vector>
#include <sstream>

#include <glm/glm.hpp>

#include <Gl/glew.h>

namespace ec
{
	Freetype::Freetype(Shader* shader)
		: m_textShader{shader}
	{
		InitFreetype();
	}

	Freetype::~Freetype()
	{
	}

	void Freetype::RenderText(const char* text, FontTextureAtlas* atlas, 
							  float x, float y, 
							  float sx, float sy,
							  const glm::vec4& color)
	{
		m_textShader->Bind();

		const unsigned char* p = (const unsigned char*)text;

		std::vector<glm::vec4> coords;

		int c = 0;

		// HACK:
		// Set the upper left corner of the first letter to the starting position
		y -= atlas->GetChar(*p).bitmapHeight * sy;

		for(; *p; p++)
		{
			auto character = atlas->GetChar(*p);
			auto atlasHeight = atlas->GetHeight();
			auto atlasWidth = atlas->GetWidth();

			float x2 = x + character.bitmapLeft * sx;
			float y2 = -y - character.bitmapTop * sy;
			float w = character.bitmapWidth * sx;
			float h = character.bitmapHeight * sy;

			x += character.advanceX * sx;
			y += character.advanceY * sy;

			if(!w || !h)
				continue;

			coords.push_back(
				glm::vec4(
					x2,
					-y2 - h,
					character.uvOffsetX,
					character.uvOffsetY + character.bitmapHeight / atlasHeight)
			);

			coords.push_back(
				glm::vec4(
					x2 + w,
					-y2,
					character.uvOffsetX + character.bitmapWidth / atlasWidth,
					character.uvOffsetY)
			);

			coords.push_back(
				glm::vec4(
					x2,
					-y2,
					character.uvOffsetX,
					character.uvOffsetY)
			);

			coords.push_back(
				glm::vec4(
					x2 + w,
					-y2,
					character.uvOffsetX + character.bitmapWidth / atlasWidth,
					character.uvOffsetY)
			);

			coords.push_back(
				glm::vec4(
					x2,
					-y2 - h,
					character.uvOffsetX,
					character.uvOffsetY + character.bitmapHeight / atlasHeight)
			);


			coords.push_back(
				glm::vec4(
					x2 + w,
					-y2 - h,
					character.uvOffsetX + character.bitmapWidth / atlasWidth,
					character.uvOffsetY + character.bitmapHeight / atlasHeight)
			);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(atlas->m_textureUniform, 0);
		glBindTexture(GL_TEXTURE_2D, atlas->m_texture);

		m_textShader->SetVec4("inputColor", color);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec4), coords.data(), GL_DYNAMIC_DRAW);

		//Generate VAO
		glBindVertexArray(m_VAO);

		//Position
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, coords.size());

		glBindVertexArray(0);
		
		//glDisable(GL_BLEND);
		m_textShader->Unbind();
	}

	void Freetype::AddFontFace(const std::string& name, const std::string& filepath)
	{
		FT_Face face;
		if(FT_New_Face(m_ftLib, filepath.c_str(), 0, &face))
		{
			printf("Couldn't load font: \"%s\"", filepath.c_str());
			return;
		}
		
		FT_Set_Pixel_Sizes(face, 24, 0);
		m_fontFaces.insert(std::pair<std::string, FT_Face>(name, face));
	}

	void Freetype::AddFontTextureAtlas(const std::string& face, unsigned int size)
	{
		auto foundFace = m_fontFaces.find(face);
		if(foundFace == m_fontFaces.end())
		{
			return;
		}

		std::ostringstream atlasName;
		atlasName << face << size;

		m_textShader->Bind();
		auto atlas = std::make_unique<FontTextureAtlas>(foundFace->second, size, m_texture);
		auto entryPair = std::make_pair(atlasName.str(), std::move(atlas));
		m_fontTextureAtlases.insert(std::move(entryPair));
		m_textShader->Unbind();
	}

	FontTextureAtlas* Freetype::GetFontTextureAtlas(const std::string& name)
	{
		auto foundAtlas = m_fontTextureAtlases.find(name);
		if(foundAtlas == m_fontTextureAtlases.end())
		{
			return nullptr;
		}
		return foundAtlas->second.get();
	}

	void Freetype::InitFreetype()
	{
		if(FT_Init_FreeType(&m_ftLib))
		{
			throw(std::exception("Couldn't initialize freetype!"));
		}
	
		m_colorIN = m_textShader->GetUniformLocation("inputColor");
		m_texture = m_textShader->GetUniformLocation("texture");

		// Create the vertex buffer object
		glGenBuffers(1, &m_VBO);
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glBindVertexArray(0);
	}
}