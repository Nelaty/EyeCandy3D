#pragma once
#include <GL/glew.h>

#include <fstream>
#include <string>

#include <glm/glm.hpp>

/*
* Bundles vertex, fragment shader, geometry, tessellation control and
* tessellation evaluation shaders.
* Geometry and tessellation shaders are optional.
*
* Includes are allowed in shader sources and referenced files will be
* inlined.
*/

namespace ec
{
	class Shader
	{
	public:
		Shader(const std::string& vertPath, 
			   const std::string& fragPath,
			   const std::string& geomPath = "",
			   const std::string& tessCtrlPath = "",
			   const std::string& tessEvalPath = "");
		~Shader();

		/* Activate this program */
		void Bind();
		void Unbind();

		/* Uniform single */
		void SetBool(const char* uniformName, const bool val);
		void SetInt(const char* uniformName, const int val);
		void SetFloat(const char* uniformName, const float val);
		void SetDouble(const char* uniformName, const double val);

		/* Uniform vector */
		void SetVec2(const char* uniformName, const glm::vec2& v);
		void SetVec3(const char* uniformName, const glm::vec3& v);
		void SetVec4(const char* uniformName, const glm::vec4& v);

		/* Uniform matrix */
		void SetMat2(const char* uniformName, const glm::mat2& m);
		void SetMat3(const char* uniformName, const glm::mat3& m);
		void SetMat4(const char* uniformName, const glm::mat4& m);

		/* Get the uniform location by name */
		GLuint GetUniformLocation(const char* uniformName);

		/* Get the program identifier */
		GLuint GetProgram() const;

	private:
		/* Read file content from path */
		std::string ReadFile(const std::string& filepath);
		
		/* Parse a line for comments and includes */
		std::string ParseLine(const std::string& line, const std::string& directory);

		/* Get the positions of a substring in another string */
		std::string GetFileStringPositions(const unsigned int pos, const std::string& str, unsigned int& start, unsigned int& end);
		
		/* Check a shader id for errors */
		GLint CheckError(GLuint shader, const char* shaderName);

		/* Compile a shader source */
		GLint CompileShader(GLuint shader, const char* path, const char* source, const char* shaderName);

		/* Load in shader sources and compile and link them */
		void LoadCompileLinkShader(const std::string& vertPath, 
								   const std::string& fragPath,
								   const std::string& geomPath, 
								   const std::string& tessCtrlPath,
								   const std::string& tessEvalPath);

		GLuint m_program;
	
		static const char* s_includeToken;
		static constexpr unsigned int s_includeTokenLength = 8;
	};
}