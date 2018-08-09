#pragma once

#include <map>
#include <string>
#include <memory>

/*
* Manages a collection of shaders.
*/
namespace ec
{
	class Shader;

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		/* Try adding a new shader */
		bool AddShader(const std::string& shaderName, 
					   const std::string& vertPath,
					   const std::string& fragPath,
					   const std::string& geomPath = "",
					   const std::string& tessCtrlPath = "",
					   const std::string& tessEvalPath = "");

		/*
		* Get a shader by its name 
		* return null if not existent
		*/
		Shader* GetShader(const char* shaderName);

		/* Return all shaders */
		const std::map<std::string, std::unique_ptr<Shader>>& GetAllShader();

		/* Try binding another shader */
		bool SwitchShaderProgram(const char* shaderName);

	private:
		std::map<std::string, std::unique_ptr<Shader>> m_shader;
	};
}