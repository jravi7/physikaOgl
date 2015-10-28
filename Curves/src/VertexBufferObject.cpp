#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject(void){}
VertexBufferObject::~VertexBufferObject(void){}

void VertexBufferObject::setVertexData(std::vector<Vertex> data)
{
	m_data = data; 
}

void VertexBufferObject::setIndices(std::vector<unsigned int> indices)
{
	m_indices = indices;
}

std::vector<unsigned int> VertexBufferObject::getIndices()
{
	return m_indices;
}
std::vector<Vertex> VertexBufferObject::getVertexData()
{
	return m_data;
}

void VertexBufferObject::createBuffers()
{
	assert(!m_indices.empty());
	assert(!m_data.empty());

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_data.size()*sizeof(Vertex), &m_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBufferObject::render(GLenum primitive)
{
	glEnableVertexAttribArray(VERTEX_POSITION);
	glEnableVertexAttribArray(VERTEX_NORMAL);
	glEnableVertexAttribArray(VERTEX_TEXTURE);
	glEnableVertexAttribArray(VERTEX_COLOR);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	glVertexAttribPointer(VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(VERTEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
	glVertexAttribPointer(VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)20);
	glVertexAttribPointer(VERTEX_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)32);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glDrawElements(primitive, m_indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(VERTEX_POSITION);
	glDisableVertexAttribArray(VERTEX_NORMAL);
	glDisableVertexAttribArray(VERTEX_TEXTURE);
	glDisableVertexAttribArray(VERTEX_COLOR);
}

void VertexBufferObject::render()
{
	glEnableVertexAttribArray(VERTEX_POSITION);
	glEnableVertexAttribArray(VERTEX_NORMAL);
	glEnableVertexAttribArray(VERTEX_TEXTURE);
	glEnableVertexAttribArray(VERTEX_COLOR);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glVertexAttribPointer(VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(VERTEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
	glVertexAttribPointer(VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)20);
	glVertexAttribPointer(VERTEX_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)32);


	glDrawArrays(GL_TRIANGLE_STRIP,0,m_data.size());

	glDisableVertexAttribArray(VERTEX_POSITION);
	glDisableVertexAttribArray(VERTEX_NORMAL);
	glDisableVertexAttribArray(VERTEX_TEXTURE);
	glDisableVertexAttribArray(VERTEX_COLOR);
}