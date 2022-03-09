#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& transform)
	:m_Mesh(mesh), m_Transform(transform), m_Material(material)
{
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	:m_Mesh(mesh), m_Material(material)
{}

GameObject::GameObject(std::shared_ptr<Mesh> mesh):m_Mesh(mesh)
{}

GameObject::~GameObject()
{}

void GameObject::SetMesh(std::shared_ptr<Mesh> mesh)
{
	m_Mesh = mesh;
}

void GameObject::SetMaterial(std::shared_ptr<Material> material)
{
	m_Material = material;
}

void GameObject::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void GameObject::Update(float g_rotX_angle, float g_rotY_angle)
{
	(*m_Mesh).UpdateBuffers();

	m_Transform.SetScale(glm::vec3(1.0f));
	m_Transform.SetTranslation(glm::vec3(0.0f, 1.0f, 0.0f));
	m_Transform.Rotate_X(g_rotX_angle);
	m_Transform.Rotate_Y(g_rotY_angle);
}

void GameObject::Draw()
{
	(*m_Mesh).Draw();
}
