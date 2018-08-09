#include "EC3D/Core/Shader/Shader.h"

#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

using namespace ec;

Shader::Shader(const std::string& vertPath, 
			   const std::string& fragPath, 
			   const std::string& geomPath, 
			   const std::string& tessCtrlPath, 
			   const std::string& tessEvalPath)
{
	LoadCompileLinkShader(vertPath, fragPath, geomPath, tessCtrlPath, tessEvalPath);
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void ec::Shader::Unbind()
{
	glUseProgram(0);
}

void ec::Shader::SetBool(const char* uniformName, const bool val)
{
	glUniform1i(glGetUniformLocation(m_program, uniformName), static_cast<int>(val));
}

void ec::Shader::SetInt(const char* uniformName, const int val)
{
	glUniform1i(glGetUniformLocation(m_program, uniformName), val);
}

void ec::Shader::SetFloat(const char* uniformName, const float val)
{
	glUniform1f(glGetUniformLocation(m_program, uniformName), val);
}

void ec::Shader::SetDouble(const char* uniformName, const double val)
{
	glUniform1d(glGetUniformLocation(m_program, uniformName), val);
}

void ec::Shader::SetVec2(const char* uniformName, const glm::vec2& v)
{
	glUniform2fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
}

void ec::Shader::SetVec3(const char* uniformName, const glm::vec3& v)
{
	glUniform3fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
}

void ec::Shader::SetVec4(const char* uniformName, const glm::vec4& v)
{
	glUniform4fv(glGetUniformLocation(m_program, uniformName), 1, glm::value_ptr(v));
}

void ec::Shader::SetMat2(const char* uniformName, const glm::mat2& m)
{
	glUniformMatrix2fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
}

void ec::Shader::SetMat3(const char* uniformName, const glm::mat3& m)
{
	glUniformMatrix3fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
}

void ec::Shader::SetMat4(const char* uniformName, const glm::mat4& m)
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName), 1, GL_FALSE, glm::value_ptr(m));
}

GLuint ec::Shader::GetUniformLocation(const char* uniformName)
{
	return glGetUniformLocation(m_program, uniformName);
}

GLuint ec::Shader::GetProgram() const
{
	return m_program;
}

std::string Shader::ReadFile(const std::string& filepath)
{
	std::string content("");
	std::ifstream in(filepath, std::ios::in);

	if(!in.is_open())
	{
		std::cerr << "ERROR: Unable to read file \"" << filepath << "\"" << std::endl;
		return content;
	}

	std::string line = "";
	std::string directory = filepath.substr(0, filepath.find_last_of("/") + 1);
	while(!in.eof())
	{
		std::getline(in, line);
		line = ParseLine(line, directory);
		content.append(line);
	}

	in.close();
	return content;
}

std::string ec::Shader::ParseLine(const std::string& line, const std::string& directory)
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
			std::string fileName = GetFileStringPositions(includePos, line, start, end);
			fileName = directory + fileName;
			std::string includedFileData = ReadFile(fileName.c_str());
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


std::string ec::Shader::GetFileStringPositions(const unsigned int pos, const std::string& str, unsigned int& start, unsigned int& end)
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

GLint ec::Shader::CheckError(GLuint shader, const char* shaderName)
{
	GLint result;
	int logLength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
	std::cout << &shaderError[0];

	return result;
}

GLint ec::Shader::CompileShader(GLuint shader, const char* path, const char* source, const char* shaderName)
{
	printf("Compiling %s shader: %s\n", shaderName, path);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	return CheckError(shader, shaderName);
}

void ec::Shader::LoadCompileLinkShader(const std::string& vertPath,
										const std::string& fragPath,
										const std::string& geomPath,
										const std::string& tessCtrlPath,
										const std::string& tessEvalPath)
{
	// Read in shader sources
	std::string vertSource = ReadFile(vertPath);
	std::string fragSource = ReadFile(fragPath);
	std::string geomSource;
	if(!geomPath.empty())  geomSource = ReadFile(geomPath);
	std::string tessCtrlSource;
	if(!tessCtrlPath.empty()) tessCtrlSource = ReadFile(tessCtrlPath);
	std::string tessEvalSource;
	if(!tessEvalPath.empty()) tessEvalSource = ReadFile(tessEvalPath);

	bool useGeometryShader = !geomSource.empty();
	bool useTessCtrlShader = !tessCtrlSource.empty();
	bool useTessEvalShader = !tessEvalSource.empty();

	// Create shaders
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geomShader;
	GLuint tessCtrlShader;
	GLuint tessEvalShader;

	GLint result = GL_FALSE;
	int logLength;

	// Compile shaders
	result = CompileShader(vertShader, vertPath.c_str(), vertSource.c_str(), "vertex");
	result = CompileShader(fragShader, fragPath.c_str(), fragSource.c_str(), "fragment");
	if(useGeometryShader)
	{
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		result = CompileShader(geomShader, geomPath.c_str(), geomSource.c_str(), "geometry");
	}
	if(useTessCtrlShader)
	{
		tessCtrlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		result = CompileShader(tessCtrlShader, tessCtrlPath.c_str(), tessCtrlSource.c_str(), "tess control");
	}
	if(useTessEvalShader)
	{
		tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		result = CompileShader(tessEvalShader, tessEvalPath.c_str(), tessEvalSource.c_str(), "tess evaluation");
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
	glGetProgramInfoLog(m_program, logLength, NULL, &programError[0]);
	std::cout << &programError[0] << std::endl;

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	if(useGeometryShader) glDeleteShader(geomShader);
	if(useTessCtrlShader) glDeleteShader(tessCtrlShader);
	if(useTessEvalShader) glDeleteShader(tessEvalShader);
}

const char* ec::Shader::s_includeToken = "#include";
