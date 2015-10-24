//Author: Jay Ravi
//Date: 08.10.2015

#pragma once
//C++
#include <vector>
//3rd Party
#include <GL/glew.h>
#include <glm\glm.hpp>

//Physika
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexBufferObject.h"

/* Discretized Plane
	A square plane defined by
	side-> no of discrete points in a side. If side is 2, there is one cell. 
	cs  -> cell size within the plane. 
*/
class DPlane
{

public:
	//
	DPlane(glm::vec3 pos, glm::vec3 color, int side, int cs);
	~DPlane(void);
	void init();
	void render(Camera *cam, std::vector<Light>& lights);
	void setShader(Shader* shader);
	void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess);

private:

	int m_cs;
	int m_side;
	glm::vec3 m_pos;
	glm::vec3 m_color; 
	std::vector<Vertex> m_data;
	std::vector<unsigned int> m_indices;

	Shader* m_shader;
	Material m_material;
	VertexBufferObject* m_vbo;
};