#pragma once
#include <GL/glew.h>
#include "ec3/Common/Common.h"

#include <glm/glm.hpp>

#include <string>


namespace ec
{
	/**
	* \brief Bundles vertex, fragment shader, geometry, tessellation
	* control and tessellation evaluation shaders.
	* Geometry and tessellation shaders are optional.
	*
	* \details Includes are allowed in shader sources. Included files
	* will be inlined. -> #include "filepath"
	*/
	class EC3D_DECLSPEC Shader
	{
	public:
		/**
		 * \brief Shader contructor.
		 * \param vertPath Path to vertex shader source.
		 * \param fragPath Path to fragment shader source.
		 * \param geomPath Path to geometry shader source.
		 * \param tessCtrlPath Path to tessellation control shader source.
		 * \param tessEvalPath Path to tessellation evaluation shader source.
		 */
		Shader(const std::string& vertPath,
		       const std::string& fragPath,
		       const std::string& geomPath = "",
		       const std::string& tessCtrlPath = "",
		       const std::string& tessEvalPath = "");
		virtual ~Shader();

		/** Activate this shader program. */
		void bind() const;
		/** Deactivate this shader program. */
		void unbind() const;

		/** Set single boolean uniform*/
		///@{
		void setBool(const char* uniformName, bool val) const;
		void setBool(int uniformLocation, bool val) const;
		///@}
		/** Set single int uniform */
		///@{
		void setInt(const char* uniformName, int val) const;
		void setInt(int uniformLocation, int val) const;
		///@}
		/** Set single float uniform */
		///@{
		void setFloat(const char* uniformName, float val) const;
		void setFloat(int uniformLocation, float val) const;
		///@}
		/** Set single double uniform */
		///@{
		void setDouble(const char* uniformName, double val) const;
		void setDouble(int uniformLocation, double val) const;
		///@}

		/** Single 2D-vector uniform */
		///@{
		void setVec2(const char* uniformName, const glm::vec2& v) const;
		void setVec2(int uniformLocation, const glm::vec2& v) const;
		///@}
		/** Single 3D-vector uniform */
		///@{
		void setVec3(const char* uniformName, const glm::vec3& v) const;
		void setVec3(int uniformLocation, const glm::vec3& v) const;
		///@}
		/** Single 4D-vector uniform */
		///@{
		void setVec4(const char* uniformName, const glm::vec4& v) const;
		void setVec4(int uniformLocation, const glm::vec4& v) const;
		///@}

		/** Single 2D-matrix uniform */
		///@{
		void setMat2(const char* uniformName, const glm::mat2& m) const;
		void setMat2(int uniformLocation, const glm::mat2& m) const;
		///@}
		/** Single 3D-matrix uniform */
		///@{
		void setMat3(const char* uniformName, const glm::mat3& m) const;
		void setMat3(int uniformLocation, const glm::mat3& m) const;
		///@}
		/** Single 4D-matrix uniform */
		///@{
		void setMat4(const char* uniformName, const glm::mat4& m) const;
		void setMat4(int uniformLocation, const glm::mat4& m) const;
		///@}

		/** Get the uniform location by name */
		GLuint getUniformLocation(const char* uniformName) const;

		/** Get the program identifier */
		GLuint getProgram() const;

		/** Can be overloaded to wrap uniform calls. */
		virtual void setUniforms();

	private:
		/** Read file content from path */
		std::string readFile(const std::string& filepath);

		/** Parse a line for comments and includes */
		std::string parseLine(const std::string& line, const std::string& directory);

		/** Get the positions of a substring in another string */
		std::string getFileStringPositions(unsigned int pos, const std::string& str, unsigned int& start,
		                                   unsigned int& end);

		/** Check a shader id for errors */
		GLint checkError(GLuint shader, const char* shaderName);

		/** Compile a shader source */
		GLint compileShader(GLuint shader, const char* path, const char* source, const char* shaderName);

		/** Load in shader sources and compile and link them */
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
