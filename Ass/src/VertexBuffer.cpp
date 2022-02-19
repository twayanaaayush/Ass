#include "VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GenBuffer();
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	GenBuffer();
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::GenBuffer()
{
	if (m_RendererID != 0) glGenBuffers(1, &m_RendererID);
	return;
}

void VertexBuffer::Update(const void* data, unsigned int size, unsigned int offset)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
