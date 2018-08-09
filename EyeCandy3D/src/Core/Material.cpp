#include "EC3D/Core/Material.h"
#include "EC3D/Core/Shader/Shader.h"

#include "EC3D/Common/Config.h"

namespace ec
{
	Material::Material()
		: m_colorAmbient{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorDiffuse{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorSpecular{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorEmissive{0.0f, 0.0f, 0.0f, 0.0f},
		m_shininess{0.0f},
		m_hasTexture{false}
	{
	}

	Material::~Material()
	{
	}

	void Material::AddTexture(const Texture& texture)
	{
		m_textures.push_back(texture);
		m_hasTexture = true;
	}

	void Material::RemoveTexture(const Texture& texture)
	{

	}

	const std::vector<Texture>& Material::GetTextures() const
	{
		return m_textures;
	}

	void Material::SetHasTexture(const bool hasTexture)
	{
		m_hasTexture = hasTexture;
	}

	bool Material::HasTexture() const
	{
		return m_hasTexture;
	}

	ec::Texture* Material::GetTexture(const unsigned int index)
	{
		if(index >= m_textures.size())
		{
			return nullptr;
		}
		return &m_textures[index];
	}

	bool Material::AddDiffuseTextureFromPath(const char* path)
	{
		Texture texture;
		bool result = texture.TextureFromFile(path, conf_shader::g_texture_diffuse);
		m_textures.push_back(texture);
		m_hasTexture = true;
		return result;
	}

	bool Material::AddSpecularTextureFromPath(const char* path)
	{
		Texture texture;
		bool result = texture.TextureFromFile(path, conf_shader::g_texture_specular);
		m_textures.push_back(texture);
		m_hasTexture = true;
		return result;
	}

	bool Material::AddBumpTextureFromPath(const char* path)
	{
		Texture texture;
		bool result = texture.TextureFromFile(path, conf_shader::g_texture_bump);
		m_textures.push_back(texture);
		m_hasTexture = true;
		return result;
	}

	void Material::SetColorAmbient(const glm::vec4& color)
	{
		m_colorAmbient = color;
	}

	void Material::SetColorAmbient(const float r, const float g, const float b, const float a)
	{
		m_colorAmbient.r = r;
		m_colorAmbient.g = g;
		m_colorAmbient.b = b;
		m_colorAmbient.a = a;
	}

	void Material::SetColorDiffuse(const glm::vec4& color)
	{
		m_colorDiffuse = color;
	}

	void Material::SetColorDiffuse(const float r, const float g, const float b, const float a)
	{
		m_colorDiffuse.r = r;
		m_colorDiffuse.g = g;
		m_colorDiffuse.b = b;
		m_colorDiffuse.a = a;
	}

	void Material::SetColorSpecular(const glm::vec4& color)
	{
		m_colorSpecular = color;
	}

	void Material::SetColorSpecular(const float r, const float g, const float b, const float a)
	{
		m_colorSpecular.r = r;
		m_colorSpecular.g = g;
		m_colorSpecular.b = b;
		m_colorSpecular.a = a;
	}

	void Material::SetColorEmissive(const glm::vec4& color)
	{
		m_colorEmissive = color;
	}

	void Material::SetColorEmissive(const float r, const float g, const float b, const float a)
	{
		m_colorEmissive.r = r;
		m_colorEmissive.g = g;
		m_colorEmissive.b = b;
		m_colorEmissive.a = a;
	}

	const glm::vec4& Material::GetColorAmbient() const
	{
		return m_colorAmbient;
	}

	const glm::vec4& Material::GetColorDiffuse() const
	{
		return m_colorDiffuse;
	}

	const glm::vec4& Material::GetColorSpecular() const
	{
		return m_colorSpecular;
	}

	const glm::vec4& Material::GetColorEmissive() const
	{
		return m_colorEmissive;
	}

	void Material::SetShininess(const float shininess)
	{
		m_shininess = shininess;
	}

	float Material::GetShininess() const
	{
		return m_shininess;
	}
}