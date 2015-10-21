//Physika X 
//Author: Jay Ravi
//Date: Oct 1st, 2015

#include "Box.h"


Box::Box(int side, glm::vec3 position, glm::vec3 color)
{
	m_side = side; 
	m_position = position; 
	m_color = color;
	m_vbo = new VertexBufferObject();
	createCube();
	fillBuffers();
}

Box::~Box(void){}

unsigned int Box::addVertexData(glm::vec3 p, glm::vec3 n)
{
	Vertex v; 
	v.p = p;
	v.t = glm::vec2((p.x+m_side*0.5f)/m_side, (p.y+m_side*0.5f)/m_side);
	v.n = n;
	v.c = glm::vec3(0.0f,0.9f,0.5f);

	m_vertex_data.push_back(v);
	return m_vertex_data.size()-1;
}

void Box::addFace(unsigned int v1, unsigned int v2, unsigned int v3)
{
	m_indices.push_back(v1);
	m_indices.push_back(v2);
	m_indices.push_back(v3);
}

void Box::createCube()
{
	glm::vec3 v1( m_side*0.5f,  m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v2(-m_side*0.5f,  m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v3(-m_side*0.5f, -m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v4( m_side*0.5f, -m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v5( m_side*0.5f,  m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v6(-m_side*0.5f,  m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v7(-m_side*0.5f, -m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v8( m_side*0.5f, -m_side*0.5f, -m_side*0.5f);

	unsigned int i1 = addVertexData(v1, glm::normalize(v1/3.f));
	unsigned int i2 = addVertexData(v2, glm::normalize(v2/3.f));
	unsigned int i3 = addVertexData(v3, glm::normalize(v3/3.f));
	unsigned int i4 = addVertexData(v4, glm::normalize(v4/3.f));
	unsigned int i5 = addVertexData(v5, glm::normalize(v5/3.f));
	unsigned int i6 = addVertexData(v6, glm::normalize(v6/3.f));
	unsigned int i7 = addVertexData(v7, glm::normalize(v7/3.f));
	unsigned int i8 = addVertexData(v8, glm::normalize(v8/3.f));

	//front
	addFace(i1, i2, i3);
	addFace(i1, i3, i4);

	//top

	addFace(i5, i6, i2);
	addFace(i5, i2, i1);

	//right

	addFace(i5, i1, i4);
	addFace(i5, i4, i8);

	//back
	addFace(i6, i5, i8);
	addFace(i6, i8, i7);

	//left
	addFace(i2, i6, i7);
	addFace(i2, i7, i3);


	//bottom
	addFace(i4, i3, i7);
	addFace(i4, i7, i8);
}

void Box::fillBuffers()
{
	m_vbo->setVertexData(m_vertex_data);
	m_vbo->setIndices(m_indices);
	m_vbo->createBuffers();
}

void Box::render()
{
	m_vbo->render(GL_TRIANGLES);
}