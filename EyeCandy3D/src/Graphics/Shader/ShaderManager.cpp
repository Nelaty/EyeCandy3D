#include "ec3/Graphics/Shader/ShaderManager.h"
#include "ec3/Graphics/Shader/Shader.h"
#include "ec3/Graphics/Shader/ShaderTimed.h"
#include "ec3/Common/Logging.h"

#include <utility>

using namespace std::string_literals;

namespace ec {

	void ShaderManager::update(const float time, const float timeDelta)
	{
		for(auto& it : m_shader)
		{
			it.second->setUniforms();
		}
		for(auto& it : m_shaderTimed)
		{
			it->update(time, timeDelta);
		}
	}

	bool ShaderManager::addShader(const std::string& shaderName, 
								  Shader_Ptr shader)
	{
		m_shader.insert(std::make_pair(shaderName, std::move(shader)));
		return true;
	}

	bool ShaderManager::addShader(const std::string& shaderName, 
								  ShaderTimed_Ptr shader)
	{
		m_shader.insert(std::make_pair(shaderName,
									   static_cast<Shader_Ptr>(std::move(shader))));
		auto temp = static_cast<ShaderTimed*>(m_shader[shaderName].get());
		m_shaderTimed.push_back(temp);
		return true;
	}


	bool ShaderManager::addShader(const std::string& shaderName,
								  const std::string& vertPath,
								  const std::string& fragPath,
								  const std::string& geomPath,
								  const std::string& tessCtrlPath,
								  const std::string& tessEvalPath)
	{
		using pair_type = std::pair<std::string, std::unique_ptr<Shader>>;

        Logger::info("(START) Adding shader: "s + shaderName);
		std::unique_ptr<Shader> shader = std::make_unique<Shader>(
			vertPath, fragPath, geomPath, tessCtrlPath, tessEvalPath);
		if(!shader)
		{
            Logger::error("(END) Adding shader: Error");
			return false;
		}
		m_shader.insert(pair_type(shaderName, std::move(shader)));
        Logger::info("(END) Adding shader: Success");
		return true;
	}

	Shader* ShaderManager::getShader(const char* shaderName) const
	{
		const auto shader = m_shader.find(shaderName);
		return shader != m_shader.end() ? shader->second.get() : nullptr;
	}

	bool ShaderManager::switchShaderProgram(const char* shaderName) const
	{
		const auto shader = getShader(shaderName);
		if(shader)
		{
			shader->bind();
			return true;
		}
		return false;
	}

	const std::map<std::string, std::unique_ptr<ec::Shader>>& ec::ShaderManager::getAllShader() const
	{
		return m_shader;
	}
}