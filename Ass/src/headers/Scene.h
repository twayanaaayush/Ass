#pragma once

#include <iostream>
#include <vector>
#include "Geometry.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

extern const float NEAR_PLANE;
extern const float FAR_PLANE;

class Scene
{
private:
	std::unique_ptr<Shader> m_GridShader;
	std::unique_ptr<Mesh> m_GridMesh;
	bool m_DrawGrid = true;

public:
	Scene(std::shared_ptr<Camera> cam);
	~Scene();

	void SetGridUniforms();
	void DrawGrid();
	void SetDrawGrid();

private:
	void InitGrid();

public:
	bool wireframe = false;
	std::shared_ptr<Camera> camera;
	//std::shared_ptr<Light> Light;
};