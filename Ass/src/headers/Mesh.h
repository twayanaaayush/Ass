#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include "Geometry.h"
#include "Material.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

using Index = unsigned int;
using Lookup = std::map<std::pair<Index, Index>, Index>;
using IndexedMesh = std::pair<std::vector<Vertex>, std::vector<Triangle>>;

class Mesh
{
protected:
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_EBO;
	BufferLayout* m_Layout;

	std::vector<Vertex> m_Vertices;
	std::vector<Triangle> m_Indices;

public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices);
	~Mesh();
	void SetVertices(std::vector<Vertex> vertices);
	void SetIndices(std::vector<Triangle> indices);

	void UpdateBuffers();
	void Draw() const;

	inline const std::vector<Vertex>& GetVertices() { return m_Vertices; }
	inline const std::vector<Triangle>& GetIndices() { return m_Indices; }

protected:
	void InitBuffers();
	IndexedMesh MakeIcosphere(int subdivisions);
	Index vertex_for_edge(Lookup& lookup, std::vector<Vertex>& vertices, Index first, Index second);
	std::vector<Triangle> Subdivide(std::vector<Vertex>& vertices, std::vector<Triangle> triangles);
};