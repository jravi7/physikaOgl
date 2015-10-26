#pragma once


//3rd Party
#include <GL\glew.h>
#include <glm\glm.hpp>

//physika
#include "Light.h"
#include "Camera.h"
#include "Vertex.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "VertexBufferObject.h"

class PObject
{
public:
	PObject(glm::vec3 position, std::string file);
	~PObject(void);

	void render(Camera* cam, std::vector<Light>& lights); 
	void setShader(Shader* shader);
	void setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess);


private: 

	glm::vec3 m_position; 
	Shader* m_shader; 
	ModelLoader* m_loader;
	Material m_material;
	VertexBufferObject* m_vbo;

};

