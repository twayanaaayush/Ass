#include "Shader.h"
#include <GLAD/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vShaderFilePath, const std::string& fShaderFilePath)
	: m_VertexPath(vShaderFilePath), m_FragmentPath(fShaderFilePath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(vShaderFilePath, fShaderFilePath);
	m_RendererID = CreateShader(source.vShaderCode, source.fShaderCode);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string vShaderFilePath, const std::string fShaderFilePath)
{
	std::string vShaderCode, fShaderCode;
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream vShaderStream, fShaderStream;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vShaderFilePath);
		fShaderFile.open(fShaderFilePath);

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << std::endl;
	}

	return { vShaderCode, fShaderCode};
}

unsigned int Shader::CreateShader(const std::string& vShaderCode, const std::string& fShaderCode)
{
	unsigned int shaderProgramID = glCreateProgram();
	unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vShaderCode);
	unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fShaderCode);

	glAttachShader(shaderProgramID, vShader);
	glAttachShader(shaderProgramID, fShader);
	glLinkProgram(shaderProgramID);
	glValidateProgram(shaderProgramID);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return shaderProgramID;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& sourceCode)
{
	int success;
	unsigned int shaderID = glCreateShader(type);
	const char* src = sourceCode.c_str();

	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*) _malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, infoLog);

		std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
			<< "::COMPILATION_FAILED\n" << infoLog << std::endl;
		
		glDeleteShader(shaderID);
		return 0;
	}

	return shaderID;
}

void Shader::Use() const
{
	glUseProgram(m_RendererID);
}

void Shader::Delete() const
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
		std::cout << "WARNING::DOESN'T EXIST::UNIFORM '" << name << "'" << std::endl;
	return location;
}

void Shader::SetUniform1f(const std::string& name, float v)
{
	glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformVec4f(const std::string& name, glm::vec4 vec)
{
	glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformVec3f(const std::string& name, glm::vec3 vec)
{
	glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}