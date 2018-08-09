#include "EC3D/Core/Shader/ShaderManager.h"
#include "EC3D/Core/Shader/Shader.h"

#include <utility>

namespace ec
{
	ShaderManager::ShaderManager()
	{
	}

	ShaderManager::~ShaderManager()
	{
	}

	bool ShaderManager::AddShader(const std::string& shaderName,
								  const std::string& vertPath,
								  const std::string& fragPath,
								  const std::string& geomPath,
								  const std::string& tessCtrlPath,
								  const std::string& tessEvalPath)
	{
		using pair_type = std::pair<std::string, std::unique_ptr<Shader>>;

		printf("ADDING NEW SHADER: %s\n", shaderName.c_str());
		std::unique_ptr<Shader> shader = std::make_unique<Shader>(
			vertPath, fragPath, geomPath, tessCtrlPath, tessEvalPath);
		if(!shader)
		{
			return false;
		}
		m_shader.insert(pair_type(shaderName, std::move(shader)));
		return true;
	}

	Shader* ShaderManager::GetShader(const char* shaderName)
	{
		Shader* shader = m_shader.find(shaderName)->second.get();
		return shader ? shader : nullptr;
	}

	bool ShaderManager::SwitchShaderProgram(const char* shaderName)
	{
		auto shader = GetShader(shaderName);
		if(shader)
		{
			shader->Bind();
			return true;
		}
		return false;
	}

	const std::map<std::string, std::unique_ptr<ec::Shader>>& ec::ShaderManager::GetAllShader()
	{
		return m_shader;
	}
}