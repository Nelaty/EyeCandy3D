#include "EC3D/Core/Freetype.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/FontTextureAtlas.h"

#include <glm/glm.hpp>

#include <vector>
#include <sstream>

namespace ec
{
	Freetype::Freetype(Shader* shader)
		: m_textShader{shader}
	{
		initFreetype();
	}

	Freetype::~Freetype()
	= default;

	void Freetype::renderText(const char* text, FontTextureAtlas* atlas, 
							  float x, float y, 
							  const float sx, const float sy,
							  const glm::vec4& color) const
	{
		m_textShader->bind();

		const auto* p = reinterpret_cast<const unsigned char*>(text);

		std::vector<glm::vec4> coords;

		auto c = 0;

		// HACK:
		// Set the upper left corner of the first letter to the starting position
		y -= atlas->getChar(*p).m_bitmapHeight * sy;

		for(; *p; p++)
		{
			const auto character = atlas->getChar(*p);
			const auto atlasHeight = atlas->getHeight();
			const auto atlasWidth = atlas->getWidth();

			const auto x2 = x + character.m_bitmapLeft * sx;
			const auto y2 = -y - character.m_bitmapTop * sy;
			const auto w = character.m_bitmapWidth * sx;
			const auto h = character.m_bitmapHeight * sy;

			x += character.m_advanceX * sx;
			y += character.m_advanceY * sy;

			if(!w || !h)
				continue;

			coords.emplace_back(
				glm::vec4(
					x2,
					-y2 - h,
					character.m_uvOffsetX,
					character.m_uvOffsetY + character.m_bitmapHeight / atlasHeight)
			);

			coords.emplace_back(
				glm::vec4(
					x2 + w,
					-y2,
					character.m_uvOffsetX + character.m_bitmapWidth / atlasWidth,
					character.m_uvOffsetY)
			);

			coords.emplace_back(
				glm::vec4(
					x2,
					-y2,
					character.m_uvOffsetX,
					character.m_uvOffsetY)
			);

			coords.emplace_back(
				glm::vec4(
					x2 + w,
					-y2,
					character.m_uvOffsetX + character.m_bitmapWidth / atlasWidth,
					character.m_uvOffsetY)
			);

			coords.emplace_back(
				glm::vec4(
					x2,
					-y2 - h,
					character.m_uvOffsetX,
					character.m_uvOffsetY + character.m_bitmapHeight / atlasHeight)
			);


			coords.emplace_back(
				glm::vec4(
					x2 + w,
					-y2 - h,
					character.m_uvOffsetX + character.m_bitmapWidth / atlasWidth,
					character.m_uvOffsetY + character.m_bitmapHeight / atlasHeight)
			);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(atlas->m_textureUniform, 0);
		glBindTexture(GL_TEXTURE_2D, atlas->m_texture);

		m_textShader->setVec4("inputColor", color);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec4), coords.data(), GL_DYNAMIC_DRAW);

		//Generate VAO
		glBindVertexArray(m_vao);

		//Position
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, coords.size());

		glBindVertexArray(0);
		
		//glDisable(GL_BLEND);
		m_textShader->unbind();
	}

	void Freetype::addFontFace(const std::string& name, const std::string& filepath)
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

	void Freetype::addFontTextureAtlas(const std::string& face, unsigned int size)
	{
		auto foundFace = m_fontFaces.find(face);
		if(foundFace == m_fontFaces.end())
		{
			return;
		}

		std::ostringstream atlasName;
		atlasName << face << size;

		m_textShader->bind();
		auto atlas = std::make_unique<FontTextureAtlas>(foundFace->second, size, m_textureLocation);
		auto entryPair = std::make_pair(atlasName.str(), std::move(atlas));
		m_fontTextureAtlases.insert(std::move(entryPair));
		m_textShader->unbind();
	}

	FontTextureAtlas* Freetype::getFontTextureAtlas(const std::string& name)
	{
		const auto foundAtlas = m_fontTextureAtlases.find(name);
		if(foundAtlas == m_fontTextureAtlases.end())
		{
			return nullptr;
		}
		return foundAtlas->second.get();
	}

	void Freetype::initFreetype()
	{
		if(FT_Init_FreeType(&m_ftLib))
		{
			throw(std::runtime_error("Couldn't initialize freetype!"));
		}
	
		m_colorLocation = m_textShader->getUniformLocation("inputColor");
		m_textureLocation = m_textShader->getUniformLocation("texture");

		// Create the vertex buffer object
		glGenBuffers(1, &m_vbo);
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		glBindVertexArray(0);
	}
}
