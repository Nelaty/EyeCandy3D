#include "EC3D/Common/Config.h"

#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Material.h"

#include <string>
#include <sstream>
#include <GL/glew.h>

namespace ec
{
	Drawable::Drawable()
		: m_geometry{nullptr},
		m_material{nullptr},
		m_shader{nullptr}
	{
	}

	Drawable::Drawable(Geometry* geometry, Material* material, Shader* shader)
		: m_geometry{geometry},
		m_material{material},
		m_shader{shader}
	{
	}

	Drawable::~Drawable()
	{
	}

	void Drawable::Init(Geometry* geometry, Material* material, Shader* shader)
	{
		m_geometry = geometry;
		m_material = material;
		m_shader = shader;
	}

	void Drawable::BeginRender(const glm::mat4& model)
	{
		m_shader->Bind();
		m_shader->SetMat4("model", model);
		SetMaterialUniforms(m_shader, m_material);
	}

	void Drawable::Render(const glm::mat4& model)
	{
		BeginRender(model);
		Render(m_shader, model);
		EndRender();
	}

	void Drawable::Render(Shader* shader, const glm::mat4& model)
	{
		m_geometry->Render(shader, model);
	}

	void Drawable::EndRender()
	{
		m_shader->Unbind();
	}

	void Drawable::SetMaterialUniforms(Shader* shader, Material* material)
	{
		if(material)
		{
			/* Set uniform flat colors */
			shader->SetVec4(conf_shader::g_material_ambient, material->GetColorAmbient());
			shader->SetVec4(conf_shader::g_material_diffuse, material->GetColorDiffuse());
			shader->SetVec4(conf_shader::g_material_specular, material->GetColorSpecular());
			shader->SetVec4(conf_shader::g_material_emissive, material->GetColorEmissive());
			shader->SetFloat(conf_shader::g_material_shininess, material->GetShininess());
			shader->SetBool(conf_shader::g_material_has_texture, material->HasTexture());

			/* Activate textures */
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			const auto& textures = material->GetTextures();
			for(unsigned int i = 0; i < textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
												  // retrieve texture number (the N in diffuse_textureN)
				std::stringstream ss;
				std::string number;
				std::string name = textures[i].GetType();
				if(name == conf_shader::g_texture_diffuse)
				{
					ss << diffuseNr++; // transfer unsigned int to stream
				}					
				else if(name == conf_shader::g_texture_specular)
				{
					ss << specularNr++; // transfer unsigned int to stream
				}					
				number = ss.str();

				shader->SetInt(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].GetId());
			}
		}
		else
		{
			/* Set uniform flat colors */
			shader->SetVec4(conf_shader::g_material_ambient, conf_shader::g_material_ambient_default);
			shader->SetVec4(conf_shader::g_material_diffuse, conf_shader::g_material_diffuse_default);
			shader->SetVec4(conf_shader::g_material_specular, conf_shader::g_material_specular_default);
			shader->SetVec4(conf_shader::g_material_emissive, conf_shader::g_material_emissive_default);
			shader->SetFloat(conf_shader::g_material_shininess, conf_shader::g_material_shininess_default);
			shader->SetBool(conf_shader::g_material_has_texture, conf_shader::g_material_has_texture_default);
		}
	}

	void Drawable::SetGeometry(Geometry* geometry)
	{
		m_geometry = geometry;
	}

	ec::Geometry* Drawable::GetGeometry()
	{
		return m_geometry;
	}

	void Drawable::SetMaterial(Material* material)
	{
		m_material = material;
	}

	ec::Material* Drawable::GetMaterial()
	{
		return m_material;
	}

	void Drawable::SetShader(Shader* shader)
	{
		m_shader = shader;
	}

	ec::Shader* Drawable::GetShader()
	{
		return m_shader;
	}
}