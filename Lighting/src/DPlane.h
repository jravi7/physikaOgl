//Author: Jay Ravi
//Date: 08.10.2015

#pragma once
//C++
#include <vector>
//3rd Party
#include <GL/glew.h>
#include <glm\glm.hpp>

//Physika
#include "ACamera.h"
#include "Shader.h"

/* Discretized Plane
	A square plane defined by
	m_side-> side of the plane in pixel
	m_cs  -> cell size within the plane. 
*/
class DPlane
{

public:
	//
	DPlane(glm::vec3 pos, int side, int cs);
	~DPlane(void);
	void init();
	void render(Shader* shader);

private:

	std::vector<unsigned int> m_indices;

	glm::vec3 m_pos; 
	glm::mat4 m_model;

	int m_cs;
	int m_side; 

	GLuint m_vbo; 
	GLuint m_nbo; 
	GLuint m_ibo;
};