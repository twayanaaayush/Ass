#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"

using RenderObjects = std::shared_ptr<std::vector<std::unique_ptr<GameObject>>>;

class Renderer
{
private:
	RenderObjects m_RenderObjects;
	std::shared_ptr<Light> m_Light;
	std::shared_ptr<Shader> m_Shader;

public:
	Renderer(RenderObjects renderObjects);
	Renderer(RenderObjects renderObjects, std::shared_ptr<Light> light);
	~Renderer();

	void AddShader(std::shared_ptr<Shader> shader);
	void UpdateAll(float g_rotX_angle, float g_rotY_angle);
	void RenderAll(Camera& camera);

};