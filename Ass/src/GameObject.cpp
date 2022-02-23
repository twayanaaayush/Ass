#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, const Material& material, const Transform& transform)
	:m_Transform(transform), m_Material(material)
{
	m_Mesh = mesh;
}

GameObject::GameObject(Mesh* mesh)
{
	m_Mesh = mesh;
}

GameObject::~GameObject()
{}

void GameObject::SetMesh(Mesh * mesh)
{
	m_Mesh = mesh;
}

void GameObject::SetMaterial(const Material& material)
{
	m_Material = material;
}

void GameObject::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void GameObject::Update()
{
	m_Mesh->UpdateBuffers();
}

void GameObject::Draw()
{
	m_Mesh->Draw();
}
