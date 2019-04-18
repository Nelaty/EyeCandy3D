#include "EC3D/Core/Shader/Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <vector>

namespace ec
{
	Shader::Shader(const std::string& vertPath,
				   const std::string& fragPath,
				   const std::string& geomPath,
				   const std::string& tessCtrlPath,
				   const std::string& tessEvalPath)
		: m_program{0}
	{
		loadCompileLinkShader(vertPath, fragPath, geomPath, tessCtrlPath, tessEvalPath);
	}

	Shader::~Shader()
	= default;

	void Shader::bind() const
	{
		glUseProgram(m_program);
	}

	void ec::Shader::unbind() const
	{
		glUseProgram(0);
	}

	void ec::Shader::setBool(const char* uniformName, const bool val) const
	{
		glUniform1i(glGetUniformLocation(m_program, uniformName), static_cast<int>(val));
	}

	void Shader::setBool(const int uniformLocation, const bool val) const
	{
		glUniform1i(uniformLocation, static_cast<int>(val));
	}

	void ec::Shader::setInt(const char* uniformName, const int val) const
	{
		glUniform1i(glGetUniformLocation(m_program, uniformName), val);
	}

	void Shader::setInt(const int uniformLocation, const int val) const
	{
		glUniform1i(uniformLocation, static_cast<int>(val));
	}

	void ec::Shader::setFloat(const char* uniformName, const float val) const
	{
		glUniform1f(glGetUniformLocation(m_program, uniformName), val);
	}

	void Shader::setFloat(const int uniformLocation, const float val) const
	{
		glUniform1f(uniformLocation, val);
	}

	void ec::Shader::setDouble(const char* uniformName, const double val) const
	{
		glUniform1d(glGetUniformLocation(m_program, uniformName), val);
	}

	void Shader::setDouble(const int uniformLocation, const double val) const
	{
		glUniform1d(uniformLocation, val);
	}

	void ec::Shader::setVec2(const char* uniformName, const glm::vec2& v) const
	{
		glUniform2fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
	}

	void Shader::setVec2(const int uniformLocation, const glm::vec2& v) const
	{
		glUniform2fv(uniformLocation, 1, glm::value_ptr(v));
	}

	void ec::Shader::setVec3(const char* uniformName, const glm::vec3& v) const
	{
		glUniform3fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
	}

	void Shader::setVec3(const int uniformLocation, const glm::vec3& v) const
	{
		glUniform3fv(uniformLocation, 1, glm::value_ptr(v));
	}

	void ec::Shader::setVec4(const char* uniformName, const glm::vec4& v) const
	{
		glUniform4fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
	}

	void Shader::setVec4(const int uniformLocation, const glm::vec4& v) const
	{
		glUniform4fv(uniformLocation, 1, glm::value_ptr(v));
	}

	void ec::Shader::setMat2(const char* uniformName, const glm::mat2& m) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
	}

	void Shader::setMat2(const int uniformLocation, const glm::mat2& m) const
	{
		glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
	}

	void ec::Shader::setMat3(const char* uniformName, const glm::mat3& m) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
	}

	void Shader::setMat3(const int uniformLocation, const glm::mat3& m) const
	{
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
	}

	void ec::Shader::setMat4(const char* uniformName, const glm::mat4& m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
	}

	void Shader::setMat4(const int uniformLocation, const glm::mat4& m) const
	{
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
	}

	GLuint ec::Shader::getUniformLocation(const char* uniformName) const
	{
		return glGetUniformLocation(m_program, uniformName);
	}

	GLuint ec::Shader::getProgram() const
	{
		return m_program;
	}

	void Shader::setUniforms()
	{
	}

	std::string Shader::readFile(const std::string& filepath)
	{
		std::string content;
		std::ifstream in(filepath, std::ios::in);

		if(!in.is_open())
		{
			std::cerr << "ERROR: Unable to read file \"" << filepath << "\"" << std::endl;
			return content;
		}

		std::string line;
		auto directory = filepath.substr(0, filepath.find_last_of('/') + 1);
		if(directory.empty())
		{
			directory = filepath.substr(0, filepath.find_last_of('\\') + 1);
		}
		while(!in.eof())
		{
			std::getline(in, line);
			line = parseLine(line, directory);
			content.append(line);
		}

		in.close();
		return content;
	}

	std::string ec::Shader::parseLine(const std::string& line, const std::string& directory)
	{
		std::string parsedLine;

		size_t includePos = 0;
		// Check for include token
		includePos = line.find(s_includeToken);
		if(includePos < line.size())
		{
			// Search for single line comment
			size_t singleLineComment = line.find_first_of("//");
			if(singleLineComment < includePos)
			{
				if(singleLineComment == 0)
				{
					singleLineComment = 1;
				}
				// Remove commented area
				parsedLine = line.substr(0, singleLineComment - 1);
			}
			else
			{
				// Inline included flie
				unsigned int start, end;
				auto fileName = getFileStringPositions(includePos, line, start, end);
				fileName = directory + fileName;
				const auto includedFileData = readFile(fileName);
				parsedLine.append(includedFileData);
			}
		}
		else
		{
			parsedLine = line;
		}

		parsedLine.append("\n");
		return parsedLine;
	}


	std::string ec::Shader::getFileStringPositions(const unsigned int pos, const std::string& str, unsigned int& start, unsigned int& end)
	{
		start = pos + s_includeTokenLength;

		while(start < str.size())
		{
			if(str[start] == '\"')
			{
				break;
			}
			++start;
		}
		++start; // Skip first '\"'
		end = start;
		while(end < str.size())
		{
			if(str[end] == '\"')
			{
				break;
			}
			++end;
		}
		end;

		std::string filepath = str.substr(start, end - start);
		return filepath;
	}

	GLint ec::Shader::checkError(GLuint shader, const char* shaderName)
	{
		GLint result;
		int logLength;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(shader, logLength, nullptr, &shaderError[0]);
		std::cout << &shaderError[0];

		return result;
	}

	GLint ec::Shader::compileShader(const GLuint shader, const char* path, const char* source, const char* shaderName)
	{
		printf("Compiling %s shader: %s\n", shaderName, path);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		return checkError(shader, shaderName);
	}

	void ec::Shader::loadCompileLinkShader(const std::string& vertPath,
										   const std::string& fragPath,
										   const std::string& geomPath,
										   const std::string& tessCtrlPath,
										   const std::string& tessEvalPath)
	{
		// Read in shader sources
		auto vertSource = readFile(vertPath);
		auto fragSource = readFile(fragPath);
		std::string geomSource;
		if(!geomPath.empty())  geomSource = readFile(geomPath);
		std::string tessCtrlSource;
		if(!tessCtrlPath.empty()) tessCtrlSource = readFile(tessCtrlPath);
		std::string tessEvalSource;
		if(!tessEvalPath.empty()) tessEvalSource = readFile(tessEvalPath);

		const auto useGeometryShader = !geomSource.empty();
		const auto useTessCtrlShader = !tessCtrlSource.empty();
		const auto useTessEvalShader = !tessEvalSource.empty();

		// Create shaders
		const auto vertShader = glCreateShader(GL_VERTEX_SHADER);
		const auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint geomShader = 0;
		GLuint tessCtrlShader = 0;
		GLuint tessEvalShader = 0;

		int logLength;

		// Compile shaders
		auto result = compileShader(vertShader, vertPath.c_str(), vertSource.c_str(), "vertex");
		result &= compileShader(fragShader, fragPath.c_str(), fragSource.c_str(), "fragment");
		if(useGeometryShader)
		{
			geomShader = glCreateShader(GL_GEOMETRY_SHADER);
			result &= compileShader(geomShader, geomPath.c_str(), geomSource.c_str(), "geometry");
		}
		if(useTessCtrlShader)
		{
			tessCtrlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
			result &= compileShader(tessCtrlShader, tessCtrlPath.c_str(), tessCtrlSource.c_str(), "tess control");
		}
		if(useTessEvalShader)
		{
			tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			result &= compileShader(tessEvalShader, tessEvalPath.c_str(), tessEvalSource.c_str(), "tess evaluation");
		}

		// Linking the program
		printf("Linking program.\n");
		m_program = glCreateProgram();
		glAttachShader(m_program, vertShader);
		glAttachShader(m_program, fragShader);
		if(useGeometryShader) glAttachShader(m_program, geomShader);
		if(useTessCtrlShader) glAttachShader(m_program, tessCtrlShader);
		if(useTessEvalShader) glAttachShader(m_program, tessEvalShader);
		glLinkProgram(m_program);

		// Print error log
		glGetProgramiv(m_program, GL_COMPILE_STATUS, &result);
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> programError((logLength > 1) ? logLength : 1);
		glGetProgramInfoLog(m_program, logLength, nullptr, &programError[0]);
		std::cout << &programError[0] << std::endl;

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		if(useGeometryShader) glDeleteShader(geomShader);
		if(useTessCtrlShader) glDeleteShader(tessCtrlShader);
		if(useTessEvalShader) glDeleteShader(tessEvalShader);
	}

	const char* ec::Shader::s_includeToken = "#include";
}