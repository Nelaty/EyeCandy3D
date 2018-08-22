#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>

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
		void bind() const;
		void unbind() const;

		/* Uniform single */
		void setBool(const char* uniformName, bool val) const;
		void setInt(const char* uniformName, int val) const;
		void setFloat(const char* uniformName, float val) const;
		void setDouble(const char* uniformName, double val) const;

		/* Uniform vector */
		void setVec2(const char* uniformName, const glm::vec2& v) const;
		void setVec3(const char* uniformName, const glm::vec3& v) const;
		void setVec4(const char* uniformName, const glm::vec4& v) const;

		/* Uniform matrix */
		void setMat2(const char* uniformName, const glm::mat2& m) const;
		void setMat3(const char* uniformName, const glm::mat3& m) const;
		void setMat4(const char* uniformName, const glm::mat4& m) const;

		/* Get the uniform location by name */
		GLuint getUniformLocation(const char* uniformName) const;

		/* Get the program identifier */
		GLuint getProgram() const;

	private:
		/* Read file content from path */
		std::string readFile(const std::string& filepath);

		/* Parse a line for comments and includes */
		std::string parseLine(const std::string& line, const std::string& directory);

		/* Get the positions of a substring in another string */
		std::string getFileStringPositions(unsigned int pos, const std::string& str, unsigned int& start,
		                                   unsigned int& end);

		/* Check a shader id for errors */
		GLint checkError(GLuint shader, const char* shaderName);

		/* Compile a shader source */
		GLint compileShader(GLuint shader, const char* path, const char* source, const char* shaderName);

		/* Load in shader sources and compile and link them */
		void loadCompileLinkShader(const std::string& vertPath,
		                           const std::string& fragPath,
		                           const std::string& geomPath,
		                           const std::string& tessCtrlPath,
		                           const std::string& tessEvalPath);

		GLuint m_program;

		static const char* s_includeToken;
		static constexpr unsigned int s_includeTokenLength = 8;
	};
}
