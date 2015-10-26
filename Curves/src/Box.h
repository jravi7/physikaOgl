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

class Box
{
public:
	Box(int side, int no_of_instances=1);
	~Box(void);
	void render(Camera* cam);

private: 
	//private methods
	void createCube();
	void fillBuffers();
	void addFace(unsigned int, unsigned int, unsigned int);
	unsigned int addVertexData(glm::vec3 v, glm::vec3 n); 

	//cube side length
	int m_side;
	int m_instances;

	std::vector<glm::vec3> m_verts;
	std::vector<glm::vec3> m_normals; 
	std::vector<unsigned int> m_indices; 

	//buffer;
	GLuint m_vbo;
	GLuint m_nbo;
	GLuint m_ibo;

};

