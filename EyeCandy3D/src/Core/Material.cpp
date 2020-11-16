#include "EC3D/Core/Material.h"
#include "EC3D/Core/Shader/Shader.h"

#include "EC3D/Common/Config.h"

#include <algorithm>

namespace ec
{
	Material::Material()
		: m_colorAmbient{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorDiffuse{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorSpecular{0.0f, 0.0f, 0.0f, 0.0f},
		m_colorEmission{0.0f, 0.0f, 0.0f, 0.0f},
		m_shininess{0.0f}
	{
	}

	Material::~Material()
	= default;

	void Material::addTexture(const Texture& texture)
	{
		m_textures.push_back(texture);
	}

	bool Material::removeTexture(const Texture& texture)
	{
		const auto removedEntry = std::remove(m_textures.begin(),
											  m_textures.end(),
											  texture);

		return removedEntry != m_textures.end();
	}

	const std::vector<Texture>& Material::getTextures() const
	{
		return m_textures;
	}

	bool Material::hasTexture() const
	{
		return !m_textures.empty();
	}

	ec::Texture* Material::getTexture(const unsigned int index)
	{
		if(index >= m_textures.size())
		{
			return nullptr;
		}
		return &m_textures[index];
	}

	bool Material::addDiffuseTextureFromPath(const std::string& path)
	{
		Texture texture;
		const auto result = texture.textureFromFile(path.c_str(), conf_shader::g_textureDiffuse);
		if(result)
		{
			addTexture(texture);
		}
		return result;
	}

	void Material::setColorAmbient(const glm::vec4& color)
	{
		m_colorAmbient = color;
	}

	void Material::setColorAmbient(const float r, const float g, const float b, const float a)
	{
		m_colorAmbient.r = r;
		m_colorAmbient.g = g;
		m_colorAmbient.b = b;
		m_colorAmbient.a = a;
	}

	void Material::setColorDiffuse(const glm::vec4& color)
	{
		m_colorDiffuse = color;
	}

	void Material::setColorDiffuse(const float r, const float g, const float b, const float a)
	{
		m_colorDiffuse.r = r;
		m_colorDiffuse.g = g;
		m_colorDiffuse.b = b;
		m_colorDiffuse.a = a;
	}

	void Material::setColorSpecular(const glm::vec4& color)
	{
		m_colorSpecular = color;
	}

	void Material::setColorSpecular(const float r, const float g, const float b, const float a)
	{
		m_colorSpecular.r = r;
		m_colorSpecular.g = g;
		m_colorSpecular.b = b;
		m_colorSpecular.a = a;
	}

	void Material::setColorEmission(const glm::vec4& color)
	{
		m_colorEmission = color;
	}

	void Material::setColorEmission(const float r, const float g, const float b, const float a)
	{
		m_colorEmission.r = r;
		m_colorEmission.g = g;
		m_colorEmission.b = b;
		m_colorEmission.a = a;
	}

	const glm::vec4& Material::getColorAmbient() const
	{
		return m_colorAmbient;
	}

	const glm::vec4& Material::getColorDiffuse() const
	{
		return m_colorDiffuse;
	}

	const glm::vec4& Material::getColorSpecular() const
	{
		return m_colorSpecular;
	}

	const glm::vec4& Material::getColorEmission() const
	{
		return m_colorEmission;
	}

	void Material::setShininess(const float shininess)
	{
		m_shininess = shininess;
	}

	float Material::getShininess() const
	{
		return m_shininess;
	}
}