#include "Mesh.h"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
{
	SetupMesh();
	setDefaultMaterial();
}

Mesh::~Mesh()
{
	delete m_VAO;
	delete m_VBO;
	delete m_EBO;
	delete m_Layout;

	delete m_Shader;
}

void Mesh::SetupMesh()
{
	m_VAO = new VertexArray();
	m_VBO = new VertexBuffer(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
	m_EBO = new IndexBuffer(&m_Indices[0], m_Indices.size());
	m_Layout = new BufferLayout();

	m_Layout->Add<Vertex>(2);	//vertex has 2 mem attribute

	m_VAO->AddBuffer(*m_VBO, *m_Layout);
	m_VAO->Unbind();
}

void Mesh::SetShader(const std::string& vShaderFilePath, const std::string& fShaderFilePath)
{
	m_Shader = new Shader(vShaderFilePath, fShaderFilePath);
}

void Mesh::Draw() const
{
	//m_Shader->Use();

	m_VAO->Bind();
	m_EBO->Bind();

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setDefaultMaterial()
{
	m_Material.ambient =  glm::vec3(1.0f, 0.5f, 0.31f);
	m_Material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	m_Material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	m_Material.shininess = 32.0f;
}