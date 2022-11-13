#include "ec3/common/config.h"

#include "ec3/graphics/drawable.h"
#include "ec3/graphics/geometry/geometry-access.h"
#include "ec3/graphics/material/material.h"
#include "ec3/graphics/shader/shader.h"

#include <string>
#include <sstream>

namespace ec
{
	Drawable::Drawable()
		: m_geometry{nullptr},
		m_material{nullptr},
		m_shader{nullptr}
	{
	}

	Drawable::Drawable(IGeometryAccess* geometry, Material* material, Shader* shader)
		: m_geometry{geometry},
		m_material{material},
		m_shader{shader}
	{
	}

	Drawable::~Drawable() = default;

	void Drawable::init(IGeometryAccess* geometry, Material* material, Shader* shader)
	{
		m_geometry = geometry;
		m_material = material;
		m_shader = shader;
	}

	void Drawable::beginRender(const glm::mat4& model)
	{
		m_shader->bind();
		m_shader->setMat4("model", model);
		setMaterialUniforms(m_shader, m_material);
	}

	void Drawable::render(const glm::mat4& model)
	{
		beginRender(model);
		render();
		endRender();
	}

	void Drawable::render()
	{
		m_geometry->render();
	}

	void Drawable::endRender()
	{
		m_shader->unbind();
	}

	void Drawable::setMaterialUniforms(Shader* shader, Material* material)
	{
		if(material)
		{
			/* Set uniform flat colors */
			shader->setVec4(conf_shader::g_materialAmbient, material->getColorAmbient());
			shader->setVec4(conf_shader::g_materialDiffuse, material->getColorDiffuse());
			shader->setVec4(conf_shader::g_materialSpecular, material->getColorSpecular());
			shader->setVec4(conf_shader::g_materialEmissive, material->getColorEmission());
			shader->setFloat(conf_shader::g_materialShininess, material->getShininess());
			shader->setBool(conf_shader::g_materialHasTexture, material->hasTexture());

			/* Activate textures */
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			const auto& textures = material->getTextures();
			for(unsigned int i = 0; i < textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
												  // retrieve texture number (the N in diffuse_textureN)
				std::stringstream ss;
				const auto name = textures[i].getType();
				if(name == conf_shader::g_textureDiffuse)
				{
					ss << diffuseNr++; // transfer unsigned int to stream
				}					
				else if(name == conf_shader::g_textureSpecular)
				{
					ss << specularNr++; // transfer unsigned int to stream
				}					
				const auto number = ss.str();

				shader->setInt(("material." + name + number).c_str(), i);
				textures[i].bind();
			}
		}
		else
		{
			/* Set uniform flat colors */
			shader->setVec4(conf_shader::g_materialAmbient, conf_shader::g_materialAmbientDefault);
			shader->setVec4(conf_shader::g_materialDiffuse, conf_shader::g_materialDiffuseDefault);
			shader->setVec4(conf_shader::g_materialSpecular, conf_shader::g_materialSpecularDefault);
			shader->setVec4(conf_shader::g_materialEmissive, conf_shader::g_materialEmissiveDefault);
			shader->setFloat(conf_shader::g_materialShininess, conf_shader::g_materialShininessDefault);
			shader->setBool(conf_shader::g_materialHasTexture, conf_shader::g_materialHasTextureDefault);
		}
	}

	void Drawable::setGeometry(IGeometryAccess* geometry)
	{
		m_geometry = geometry;
	}

	ec::IGeometryAccess* Drawable::getGeometry() const
	{
		return m_geometry;
	}

	void Drawable::setMaterial(Material* material)
	{
		m_material = material;
	}

	ec::Material* Drawable::getMaterial() const
	{
		return m_material;
	}

	void Drawable::setShader(Shader* shader)
	{
		m_shader = shader;
	}

	ec::Shader* Drawable::getShader() const
	{
		return m_shader;
	}
}