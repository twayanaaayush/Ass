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
	m_GridMesh = std::make_unique<Mesh>(Plane::grid, Plane::gridIndices);
}

void Scene::SetGridUniforms(Shader& shader)
{
	glm::mat4 projection = glm::perspective((*camera).GetZoom(), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), NEAR_PLANE, FAR_PLANE);
	glm::mat4 view = (*camera).GetViewMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	shader.SetUniform1f("nearPlane", NEAR_PLANE);
	shader.SetUniform1f("farPlane", FAR_PLANE);
	shader.SetUniformMat4f("projection", projection);
	shader.SetUniformMat4f("view", view);
}

void Scene::DrawGrid()
{
	(*m_GridMesh).Draw();
}