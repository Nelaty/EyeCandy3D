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

	ec::Material Material::createFromColor(const Color& color)
	{
		Material material;
		material.setColorDiffuse(color);
		return material;
	}

	ec::Material Material::createFromTexture(const Texture& texture)
	{
		Material material;
		material.addTexture(texture);
		return material;
	}

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

	bool Material::addDiffuseTextureFromPath(const char* path)
	{
		Texture texture;
		const auto result = texture.textureFromFile(path, conf_shader::g_textureDiffuse);
		if(result)
		{
			addTexture(texture);
		}
		return result;
	}

	void Material::setColorAmbient(const float r, const float g, const float b, const float a)
	{
		m_colorAmbient = Color::createRgbF(r, g, b, a);
	}

	void Material::setColorAmbient(const Color& color)
	{
		m_colorAmbient = color;
	}

	void Material::setColorDiffuse(const float r, const float g, const float b, const float a)
	{
		m_colorDiffuse = Color::createRgbF(r, g, b, a);
	}

	void Material::setColorDiffuse(const Color& color)
	{
		m_colorDiffuse = color;
	}

	void Material::setColorSpecular(const float r, const float g, const float b, const float a)
	{
		m_colorSpecular = Color::createRgbF(r, g, b, a);
	}

	void Material::setColorSpecular(const Color& color)
	{
		m_colorSpecular = color;
	}

	void Material::setColorEmission(const float r, const float g, const float b, const float a)
	{
		m_colorEmission = Color::createRgbF(r, g, b, a);
	}

	void Material::setColorEmission(const Color& color)
	{
		m_colorEmission = color;
	}

	const ec::Color& Material::getColorAmbient() const
	{
		return m_colorAmbient;
	}

	const ec::Color& Material::getColorDiffuse() const
	{
		return m_colorDiffuse;
	}

	const ec::Color& Material::getColorSpecular() const
	{
		return m_colorSpecular;
	}

	const ec::Color& Material::getColorEmission() const
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