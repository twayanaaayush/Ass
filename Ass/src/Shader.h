#pragma once

#include <string>

struct ShaderProgramSource
{
	std::string vShaderCode;
	std::string fShaderCode;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_VertexPath, m_FragmentPath;

public:
	Shader(const std::string& vShaderFilePath, const std::string& fShaderFilePath);
	~Shader();
	
	void Use() const;
	void Delete() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	ShaderProgramSource ParseShader(const std::string vShaderFilePath, const std::string fShaderFilePath);
	unsigned int CreateShader(const std::string& vShaderCode, const std::string& fShaderCode);
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
	int GetUniformLocation(const std::string& name);
};