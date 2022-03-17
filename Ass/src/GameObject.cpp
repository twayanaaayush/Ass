#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& transform)
	:m_Mesh(mesh), m_Transform(transform), m_Material(material), m_Size(1.0f)
{
	CalculateBoundingBox();
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
	:m_Mesh(mesh), m_Material(material), m_Size(1.0f)
{
	CalculateBoundingBox();
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh):m_Mesh(mesh), m_Size(1.0f)
{
	CalculateBoundingBox();
}

GameObject::~GameObject()
{}

void GameObject::SetMesh(std::shared_ptr<Mesh> mesh)
{
	m_Mesh = mesh;
	CalculateBoundingBox();
}

void GameObject::SetMaterial(std::shared_ptr<Material> material)
{
	m_Material = material;
}

void GameObject::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}

void GameObject::SetSize(float size)
{
	m_Size = size;
	m_Transform.SetScale(glm::vec3(m_Size));
}

void GameObject::CalculateBoundingBox()
{
	float minX = 0.0f, minY = 0.0f, minZ = 0.0f;
	float maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;

	for (auto it = (*m_Mesh).GetVertices().begin(); it != (*m_Mesh).GetVertices().end(); ++it)
	{
		if ((*it).Position.x > maxX) maxX = (*it).Position.x;
		if ((*it).Position.x < minX) minX = (*it).Position.x;
		
		if ((*it).Position.y > maxY) maxY = (*it).Position.y;
		if ((*it).Position.y < minY) minY = (*it).Position.y;
		
		if ((*it).Position.z > maxZ) maxZ = (*it).Position.z;
		if ((*it).Position.z < minZ) minZ = (*it).Position.z;
	}
	m_BoundingBox[0] = glm::vec3(minX, minY, minZ);
	m_BoundingBox[1] = glm::vec3(maxX, maxY, maxZ);
}


void GameObject::Update(bool BEGIN_SIMULATION, float g_rotX_angle, float g_rotY_angle)
{
	(*m_Mesh).UpdateBuffers();
	CalculateBoundingBox();

	m_Transform.SetScale(glm::vec3(m_Size));
	m_Transform.SetTranslation(glm::vec3(0.0f, 1.0f, 0.0f));
	m_Transform.Rotate_X(g_rotX_angle);
	m_Transform.Rotate_Y(g_rotY_angle);
}

void GameObject::Draw()
{
	(*m_Mesh).Draw();
}
