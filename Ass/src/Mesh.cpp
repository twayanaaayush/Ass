#include "Mesh.h"

Mesh::Mesh()
{
	auto icosphereIndexedMesh = MakeIcosphere(1);
	SetVertices(icosphereIndexedMesh.first);
	SetIndices(icosphereIndexedMesh.second);

	InitBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices)
	: m_Vertices(vertices), m_Indices(indices)
{
	InitBuffers();
}

Mesh::~Mesh()
{
	delete m_VAO;
	delete m_VBO;
	delete m_EBO;
	delete m_Layout;
}

void Mesh::SetVertices(std::vector<Vertex> vertices)
{
	m_Vertices = vertices;
}

void Mesh::SetIndices(std::vector<Triangle> indices)
{
	m_Indices = indices;
}

void Mesh::InitBuffers()
{
	m_VAO = new VertexArray();
	m_VBO = new VertexBuffer(&m_Vertices[0], (unsigned int)(m_Vertices.size() * sizeof(Vertex)));
	m_EBO = new IndexBuffer(reinterpret_cast<unsigned int*>(&m_Indices[0]), m_Indices.size() * Triangle::GetVertexCount());
	m_Layout = new BufferLayout();

	m_Layout->Add<float>(3);
	
	m_VAO->AddBuffer(*m_VBO, *m_Layout);
	m_VAO->Unbind();
}

void Mesh::UpdateBuffers()
{
	m_VBO->Update(&m_Vertices[0], (unsigned int)(m_Vertices.size() * sizeof(Vertex)));
}

void Mesh::Draw() const
{
	m_VAO->Bind();
	m_EBO->Bind();

	glDrawElements(GL_TRIANGLES, m_Indices.size() * Triangle::GetVertexCount(), GL_UNSIGNED_INT, 0);
}

Index Mesh::vertex_for_edge(Lookup& lookup, std::vector<Vertex>& vertices, Index first, Index second)
{
	Lookup::key_type key(first, second);

	if (key.first > key.second) std::swap(key.first, key.second);

	auto inserted = lookup.insert({ key, vertices.size() });
	if (inserted.second)
	{
		auto& edge0 = vertices[first];
		auto& edge1 = vertices[second];
		auto point = glm::normalize(edge0.Position + edge1.Position);
		vertices.push_back({ point });
	}

	return inserted.first->second;
}

std::vector<Triangle> Mesh::Subdivide(std::vector<Vertex>& vertices, std::vector<Triangle> triangles)
{
	Lookup lookup;
	std::vector<Triangle> result;

	for (auto&& each : triangles)
	{
		std::array<Index, 3> mid;
		for (int edge = 0; edge < 3; ++edge)
		{
			mid[edge] = vertex_for_edge(lookup, vertices,
				each.vertex[edge], each.vertex[(edge + 1) % 3]);
		}

		result.push_back({ each.vertex[0], mid[0], mid[2] });
		result.push_back({ each.vertex[1], mid[1], mid[0] });
		result.push_back({ each.vertex[2], mid[2], mid[1] });
		result.push_back({ mid[0], mid[1], mid[2] });
	}

	return result;
}

IndexedMesh Mesh::MakeIcosphere(int subdivisions)
{
	std::vector<Vertex> vertices = icosahedron::vertices;
	std::vector<Triangle> triangles = icosahedron::triangles;

	for (int i = 0; i < subdivisions; ++i)
	{
		triangles = Subdivide(vertices, triangles);
	}

	return { vertices, triangles };
}
