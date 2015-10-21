//Author: Jay Ravi
//Date: Oct 21st 2015

#pragma once

//C++
#include <vector>

//3rd party
#include <gl\glew.h>

//Physika
#include "Vertex.h"



class VertexBufferObject
{
public:
	VertexBufferObject(void);
	~VertexBufferObject(void);

	void render(GLenum primitive);
	void createBuffers();
	void setVertexData(std::vector<Vertex> data);
	void setIndices(std::vector<unsigned int> indices);

	std::vector<Vertex> getVertexData();
	std::vector<unsigned int> getIndices();

private: 

	GLuint m_vbo; 
	GLuint m_ibo;

	std::vector<Vertex> m_data; 
	std::vector<unsigned int> m_indices; 

};

