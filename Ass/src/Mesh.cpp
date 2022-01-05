#include "Mesh.h"

//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices)
//	: m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
//{
//	InitBuffers();
//	AddMaterial();
//}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
{
	InitBuffers();
	AddMaterial();
}

Mesh::~Mesh()
{
	delete m_VAO;
	delete m_VBO;
	delete m_EBO;
	delete m_Layout;
}

void Mesh::InitBuffers()
{
	m_VAO = new VertexArray();
	m_VBO = new VertexBuffer(&m_Vertices[0], (unsigned int)(m_Vertices.size() * sizeof(Vertex)));
	m_EBO = new IndexBuffer(reinterpret_cast<unsigned int*>(&m_Indices[0]), m_Indices.size());
	m_Layout = new BufferLayout();

	m_Layout->Add<Vertex>(2);	//vertex has 2 mem attribute

	m_VAO->AddBuffer(*m_VBO, *m_Layout);
	m_VAO->Unbind();
}

void Mesh::Draw() const
{
	m_VAO->Bind();
	m_EBO->Bind();

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::AddMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	m_Material.ambient = ambient;
	m_Material.diffuse = diffuse;
	m_Material.specular = specular;
	m_Material.shininess = shininess;
}
