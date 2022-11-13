#include "ec3/graphics/material/texture.h"
#include "ec3/common/logging.h"

#define STB_IMAGE_IMPLEMENTATION  
#include "stb/stb_image.h"

using namespace std::string_literals;

namespace ec {

	Texture::Texture()
		: m_initialized{false},
		m_id(0), 
		m_width(0),
		m_height(0),
		m_componentNum(0),
		m_dimension()
	{
	}

	Texture::~Texture()
	= default;

	bool Texture::operator==(const Texture& texture) const
	{
		return getId() == texture.getId();
	}

	void Texture::bind() const
	{
		assert(m_initialized);

		glBindTexture(m_dimension, m_id);
	}

	void Texture::unbind() const
	{
		glBindTexture(m_dimension, 0);
	}

	void Texture::setType(const std::string& type)
	{
		m_type = type;
	}

	int Texture::getId() const
	{
		return m_id;
	}

	const std::string& Texture::getType() const
	{
		return m_type;
	}

	ec::TextureTypes::Dimensions Texture::getDimensions() const
	{
		return m_dimension;
	}

	bool Texture::textureFromFile(std::string_view path, std::string_view type)
	{
		if(m_initialized)
		{
			return false;
		}

		glGenTextures(1, &m_id);

		auto result = false;
		auto* data = stbi_load(path.data(), &m_width, &m_height, &m_componentNum, 0);
		if(data)
		{
			result = true;

			GLenum format;
			if(m_componentNum == 1)
			{
				format = GL_RED;
			}
			else if(m_componentNum == 3)
			{
				format = GL_RGB;
			}
			else if(m_componentNum == 4)
			{
				format = GL_RGBA;
			}
			else
			{
				result = false;
			}

			if(result)
			{
				glBindTexture(GL_TEXTURE_2D, m_id);
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glBindTexture(GL_TEXTURE_2D, 0);

				m_initialized = true;
			}
		}

		stbi_image_free(data);

		m_type = type;
		m_dimension = TextureTypes::Dimensions::texture_2d;

		if(!result)
		{
            Logger::error("Texture failed to load: "s + path.data());
		}
		return result;
	}

	bool Texture::cubeMapFromFile(std::string_view path, std::string_view type)
	{
		if(m_initialized)
		{
			return false;
		}

		glGenTextures(1, &m_id);

		auto result = false;
		auto* data = stbi_load(path.data(), &m_width, &m_height, &m_componentNum, 0);
		if(data)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);

			m_initialized = true;
			result = true;
		}
		stbi_image_free(data);
		

		m_dimension = TextureTypes::Dimensions::texture_3d;

		if(!result)
		{
            Logger::error("Texture failed to load: "s + path.data());
		}
		return result;
	}

	int Texture::getWidth() const
	{
		return m_width;
	}

	int Texture::getHeight() const
	{
		return m_height;
	}

	int Texture::getComponentNum() const
	{
		return m_componentNum;
	}

	bool Texture::isInitialized() const
	{
		return m_initialized;
	}

	void Texture::free()
	{
		if(!isInitialized()) return;
		
		glDeleteTextures(1, &m_id);
		m_initialized = false;

		m_width = 0;
		m_height = 0;
		m_componentNum = 0;
		m_type = "";
	}

	const std::string& TextureTypes::getTypeString(const Type type)
	{
		return s_textureTypes.find(type)->second;
	}

	// TODO: centralized magic value keeping -> put this in config file
	const std::map<ec::TextureTypes::Type, std::string> TextureTypes::s_textureTypes =
	{
		{ Type::texture_diffuse, "texture_diffuse" },
		{ Type::texture_specular, "texture_specular" },
		{ Type::texture_bump, "texture_bump" }
	};
}