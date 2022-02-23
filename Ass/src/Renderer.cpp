#include "Renderer.h"

Renderer::Renderer(std::vector<GameObject>* renderObjects)
{
	m_RenderObjects = renderObjects;
}

Renderer::Renderer(std::vector<GameObject>* renderObjects, std::vector<Light>* lights)
{
	m_RenderObjects = renderObjects;
	m_Lights = lights;
}

Renderer::~Renderer()
{
	delete m_Shader;
}

void Renderer::AddShader(const std::string& vShaderFilePath, const std::string& fShaderFilePath)
{
	m_Shader = new Shader(vShaderFilePath, fShaderFilePath);
}

void Renderer::RenderAll(Camera& camera)
{
}
