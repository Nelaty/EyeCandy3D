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
	= default;

	void Material::addTexture(const Texture& texture)
	{
		m_textures.push_back(texture);
		m_hasTexture = true;
	}

	void Material::removeTexture(const Texture& texture)
	{

	}

	const std::vector<Texture>& Material::getTextures() const
	{
		return m_textures;
	}

	void Material::setHasTexture(const bool hasTexture)
	{
		m_hasTexture = hasTexture;
	}

	bool Material::hasTexture() const
	{
		return m_hasTexture;
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
		m_textures.push_back(texture);
		m_hasTexture = true;
		return result;
	}

	bool Material::addSpecularTextureFromPath(const char* path)
	{
		Texture texture;
		const auto result = texture.textureFromFile(path, conf_shader::g_textureSpecular);
		m_textures.push_back(texture);
		m_hasTexture = true;
		return result;
	}

	bool Material::addBumpTextureFromPath(const char* path)
	{
		Texture texture;
		const auto result = texture.textureFromFile(path, conf_shader::g_textureBump);
		m_textures.push_back(texture);
		m_hasTexture = true;
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

	void Material::setColorEmissive(const glm::vec4& color)
	{
		m_colorEmissive = color;
	}

	void Material::setColorEmissive(const float r, const float g, const float b, const float a)
	{
		m_colorEmissive.r = r;
		m_colorEmissive.g = g;
		m_colorEmissive.b = b;
		m_colorEmissive.a = a;
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

	const glm::vec4& Material::getColorEmissive() const
	{
		return m_colorEmissive;
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