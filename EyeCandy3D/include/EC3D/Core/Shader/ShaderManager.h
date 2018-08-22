#pragma once

#include <map>
#include <string>
#include <memory>

/**
* Manages a collection of shaders.
*/
namespace ec
{
	class Shader;

	class ShaderManager
	{
	public:
		explicit ShaderManager();
		~ShaderManager();

		/** Try to add a new shader */
		bool addShader(const std::string& shaderName, 
					   const std::string& vertPath,
					   const std::string& fragPath,
					   const std::string& geomPath = "",
					   const std::string& tessCtrlPath = "",
					   const std::string& tessEvalPath = "");

		/**
		* Get a shader by its name 
		* return null if not existent
		*/
		Shader* getShader(const char* shaderName) const;

		/** Return all shaders */
		const std::map<std::string, std::unique_ptr<Shader>>& getAllShader() const;

		/** Try binding another shader */
		bool switchShaderProgram(const char* shaderName) const;

	private:
		std::map<std::string, std::unique_ptr<Shader>> m_shader;
	};
}