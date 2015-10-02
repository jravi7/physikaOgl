//Physika X 
//Author: Jay Ravi
//Date: Oct 1st, 2015

#include "Box.h"


Box::Box(int side, int no_of_instances)
{
	m_side = side; 
	m_instances = no_of_instances;
	createCube();
	fillBuffers();
}

Box::~Box(void){}

unsigned int Box::addVertexData(glm::vec3 v, glm::vec3 n)
{
	m_verts.push_back(v);
	m_normals.push_back(n);
	assert(m_verts.size()==m_normals.size());
	assert(m_verts.size()!=0);
	return m_verts.size()-1;
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
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_verts.size()*sizeof(glm::vec3), &m_verts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_nbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Box::render(Camera* cam)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	//glDrawArrays(GL_TRIANGLES, 0, m_verts.size());
	glDrawElementsInstanced(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0, m_instances);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}