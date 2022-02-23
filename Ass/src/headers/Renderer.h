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
	Shader* m_Shader = nullptr;

public:
	Renderer(std::vector<GameObject>* renderObjects);
	Renderer(std::vector<GameObject>* renderObjects, std::vector<Light>* lights);
	~Renderer();

	void AddShader(const std::string& vShaderFilePath, const std::string& fShaderFilePath);
	void RenderAll(Camera& camera);

};