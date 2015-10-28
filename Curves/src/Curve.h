#pragma once


#define M_PI 3.14159265358979323846
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
	void setShader(Shader* shader, Shader* shader2);
	void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess);

private:
	
	int m_count;
	std::vector<Vertex> m_points;
	std::vector<Vertex> m_circle_points;
	std::vector<unsigned int> m_indices;
	std::vector<unsigned int> m_indices2;
	Shader* m_shader; 
	Shader* m_shader2; 
	Material m_material;
	glm::vec3 m_position; 
	VertexBufferObject* m_vbo;
	VertexBufferObject* m_vbo2;
};

