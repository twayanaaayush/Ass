#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>


Scene::Scene(std::shared_ptr<Camera> cam)
{
	InitGrid();
	//camera = std::make_shared<Camera>(glm::vec3(0.0f, 1.5f, 6.0f));
	camera = cam;
}

Scene::~Scene()
{
}

void Scene::InitGrid()
{
	m_GridMesh = std::make_unique<Mesh>(plane::grid, plane::gridIndices);
	m_GridShader = std::make_unique<Shader>("res/shaders/GridVertex.shader", "res/shaders/GridFragment.shader");
}

void Scene::SetGridUniforms()
{
	glm::mat4 projection = glm::perspective((*camera).GetZoom(), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), NEAR_PLANE, FAR_PLANE);
	glm::mat4 view = (*camera).GetViewMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	(*m_GridShader).Use();
	(*m_GridShader).SetUniform1f("nearPlane", NEAR_PLANE);
	(*m_GridShader).SetUniform1f("farPlane", FAR_PLANE);
	(*m_GridShader).SetUniformMat4f("projection", projection);
	(*m_GridShader).SetUniformMat4f("view", view);
}

void Scene::DrawGrid()
{
	if (m_DrawGrid) (*m_GridMesh).Draw();
}

void Scene::SetDrawGrid()
{
	m_DrawGrid = !m_DrawGrid;
}