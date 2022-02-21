#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"

class Renderer
{
private:
	std::vector<GameObject>* m_RenderObjects = nullptr;
	std::vector<Light>* m_Lights = nullptr;
	Shader m_Shader;

public:
	Renderer() = default;
	Renderer(const Renderer& other);
	Renderer(std::vector<GameObject>* renderObjects);
	Renderer(std::vector<GameObject>* renderObjects, std::vector<Light>* lights);

	void AddShader(const std::string& vShaderFilePath, const std::string& fShaderFilePath);
	void AddShader(Shader& shader);
	void AddShader();
	void RenderAll(Camera& camera);

};