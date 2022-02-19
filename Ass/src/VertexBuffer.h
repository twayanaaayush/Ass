#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(unsigned int size);	
	~VertexBuffer();

	void GenBuffer();
	void Bind() const;
	void Unbind() const;
	void Update(const void* data, unsigned int size, unsigned int offset = 0);

};