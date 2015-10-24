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
#include "Light.h"
#include "Camera.h"
#include "Vertex.h"
#include "Shader.h"
#include "VertexBufferObject.h"

class Light;

class Box
{
public:
	Box(int side, glm::vec3 position, glm::vec3 color);
	~Box(void);
	void render(Camera* cam);
	void render(Camera* cam, std::vector<Light>& lights);
	void setShader(Shader* shader);
	void setPosition(glm::vec3);
	void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess);

private: 
	//private methods
	void createCube();
	void fillBuffers();
	void addFace(unsigned int, unsigned int, unsigned int);
	unsigned int addVertexData(glm::vec3 v, glm::vec3 n); 

private: 

	//cube side length
	int m_side;
	glm::vec3 m_color;
	glm::vec3 m_position;
	std::vector<Vertex> m_vertex_data; 
	std::vector<unsigned int> m_indices;


	Shader* m_shader; 
	Material m_material;
	VertexBufferObject* m_vbo; 
	
};

