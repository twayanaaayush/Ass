#include <GLAD/glad.h>

#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& VBO, const BufferLayout& layout)
{
	Bind();
	VBO.Bind();

	const std::vector<VertexAttrib>& attribs = layout.GetAttribs();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < attribs.size(); i++)
	{
		const VertexAttrib& attrib = attribs[i];
		glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);

		offset += attrib.count * sizeof(attrib.type);
	}

}

