#pragma once

#include <GLAD/glad.h>
#include <vector>

struct VertexAttrib
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

class BufferLayout
{
private:
	std::vector<VertexAttrib> m_Attribs;
	unsigned int m_Stride;

public:
	BufferLayout() :m_Stride(0) {}

	template<typename T>
	void Add(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Add<float>(unsigned int count)
	{
		m_Attribs.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * sizeof(GL_FLOAT);
	}

	template<>
	void Add<unsigned int>(unsigned int count)
	{
		m_Attribs.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Add<unsigned char>(unsigned int count)
	{
		m_Attribs.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VertexAttrib>& GetAttribs() const
	{
		return m_Attribs;
	}

	inline unsigned int GetStride() const
	{
		return m_Stride;
	}

};