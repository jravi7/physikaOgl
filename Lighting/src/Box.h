//Physika X 
//Author: Jay Ravi
//Date: Oct 1st, 2015

#pragma once

//C++
#include<vector>

//3rd Party
#include <GL\glew.h>
#include <glm\glm.hpp>

//Physika
#include "Camera.h"
#include "Vertex.h"
#include "VertexBufferObject.h"

class Box
{
public:
	Box(int side, glm::vec3 position, glm::vec3 color);
	~Box(void);
	void render();

private: 
	//private methods
	void createCube();
	void fillBuffers();
	void addFace(unsigned int, unsigned int, unsigned int);
	unsigned int addVertexData(glm::vec3 v, glm::vec3 n); 

private: 

	//cube side length
	int m_side;

	glm::vec3 m_position;
	glm::vec3 m_color;
	std::vector<Vertex> m_vertex_data; 
	std::vector<unsigned int> m_indices;


	VertexBufferObject* m_vbo; 
	Shader* m_shader; 

	

};

