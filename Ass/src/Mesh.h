#pragma once

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Geometry.h"
#include "Material.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Mesh
{
private:
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_EBO;
	BufferLayout* m_Layout;

	// mesh data
	//std::vector<Vertex> m_Vertices;
	std::vector<Vertex_P> m_Vertices;
	//std::vector<Triangle> m_Indices;
	std::vector<unsigned int> m_Indices;

	// material data
	Material m_Material;

public:
	//Mesh(std::vector<Vertex> vertices, std::vector<Triangle> indices);
	//Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex_P> vertices, std::vector<unsigned int> indices);
	~Mesh();
	void Draw() const;
	void AddMaterial(
		glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
		float shininess = 32.0f
	);
	inline Material GetMaterial() { return m_Material; }	// pass reference

private:
	void InitBuffers();
};