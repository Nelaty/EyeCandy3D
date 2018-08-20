#include "EC3D/Core/Texture.h"

#define STB_IMAGE_IMPLEMENTATION  
#include "stb_image.h"

namespace ec
{
	Texture::Texture()
		: m_id{-1}
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::SetId(const unsigned int id)
	{
		m_id = id;
	}

	void Texture::SetType(const std::string& type)
	{
		m_type = type;
	}

	int Texture::GetId() const
	{
		return m_id;
	}

	const std::string& Texture::GetType() const
	{
		return m_type;
	}

	ec::TextureTypes::Dimensions Texture::GetDimensions() const
	{
		return m_dimension;
	}

	bool Texture::TextureFromFile(const char* path, const std::string& type)
	{
		unsigned int textureID = 0;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		bool result = false;

		unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
		if(data)
		{
			result = true;

			GLenum format;
			if(nrComponents == 1)
				format = GL_RED;
			else if(nrComponents == 3)
				format = GL_RGB;
			else if(nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		else
		{
			printf("Texture failed to load at path: %s\n", path);
			stbi_image_free(data);
		}

		m_type = type;
		m_id = textureID;
		m_dimension = TextureTypes::Dimensions::texture_2D;

		return result;
	}

	bool Texture::CubeMapFromFile(const char* path, const std::string& type)
	{
		unsigned int textureID = 0;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		bool result = false;

		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if(data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			
			result = true;
			stbi_image_free(data);
		}
		else
		{
			printf("Texture failed to load at path: %s\n", path);
			stbi_image_free(data);
			
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		m_dimension = TextureTypes::Dimensions::texture_3D;
		return result;
	}

	bool Texture::IsInitialized() const
	{
		return m_id != -1;
	}

	void Texture::Free()
	{
		if(!IsInitialized()) return;
		
		GLuint id = m_id;
		glDeleteTextures(1, &id);
		m_id = -1;
	}

	const std::string& TextureTypes::GetTypeString(const Type type)
	{
		return s_textureTypes.find(type)->second;
	}

	const std::map<ec::TextureTypes::Type, std::string> TextureTypes::s_textureTypes =
	{
		{ Type::texture_diffuse, "texture_diffuse" },
		{ Type::texture_specular, "texture_specular" },
		{ Type::texture_bump, "texture_bump" }
	};
}