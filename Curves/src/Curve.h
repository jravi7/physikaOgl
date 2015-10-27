#pragma once

//3rd Party
#include <GL\glew.h>
#include <glm\glm.hpp>

//physika
#include "Light.h"
#include "Camera.h"
#include "Vertex.h"
#include "Shader.h"
#include "Vertex.h"
#include "VertexBufferObject.h"


class Curve
{
public:
	Curve(int points);
	~Curve(void);

	void init();
	void render(Camera* cam, std::vector<Light>& lights); 
	void setShader(Shader* shader);
	void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess);

private:
	
	int m_count;
	std::vector<Vertex> m_points;
	std::vector<unsigned int> m_indices;
	Shader* m_shader; 
	Material m_material;
	glm::vec3 m_position; 
	VertexBufferObject* m_vbo;
};

