#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& VBO, const BufferLayout& layout);
};