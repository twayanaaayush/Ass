#pragma once

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Mesh
{
private:
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_EBO;
	BufferLayout* m_Layout;

	// mesh data
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

public:
	Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices);
	~Mesh();
	void Draw() const;

private:
	void setupMesh();
};