#pragma once

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Material.h"
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

	// shader data
	Shader* m_Shader;

	// mesh data
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	// material data
	Material m_Material;

public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();
	void Draw() const;
	void setDefaultMaterial();
	void SetShader(const std::string& vShaderFilePath, const std::string& fShaderFilePath);
	inline Shader& GetShader() const { return *m_Shader; }
	inline Material GetMaterial() { return m_Material; }	// pass reference

private:
	void SetupMesh();
};