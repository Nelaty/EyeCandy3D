#pragma once
#include "ec3/Common/Common.h"

#include <map>
#include <string>
#include <vector>
#include <memory>

/**
* \brief Manages a collection of shaders.
*/
namespace ec
{
	class Shader;
	class ShaderTimed;

	class EC3D_DECLSPEC ShaderManager
	{
	public:
		using Shader_Ptr = std::unique_ptr<Shader>;
		using ShaderTimed_Ptr = std::unique_ptr<ShaderTimed>;

		explicit ShaderManager() = default;
		~ShaderManager() = default;

		/** 
		 * Update times of timed shaders and uniforms of all shaders.
		 */
		void update(float time, float timeDelta);

		/**
		 * Add an existing shader.
		 */
		bool addShader(const std::string& shaderName, Shader_Ptr shader);

		/**
		 * Add an existing shader, which will be updated continuously.
		 */
		bool addShader(const std::string& shaderName, ShaderTimed_Ptr shader);

		/** 
		 * Create and add a new shader
		 */
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
		std::vector<ShaderTimed*> m_shaderTimed;
	};
}