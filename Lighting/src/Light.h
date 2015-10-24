//Author: Jay Ravi
//Date: 10.10.2015

#pragma once
//3rd Party
#include <glm\glm.hpp>

//Physika
#include "Box.h"
#include "Shader.h"
#include "Camera.h"

class Box;

class Light
{	
public:
	struct Property
	{
		glm::vec3 la; 
		glm::vec3 ld;
		glm::vec3 ls;
	};

	enum Type {DIRECTIONAL, POINT, SPOT};

	Light(glm::vec3 pos);
	~Light();

	void render(Camera* cam);
	void setProperty(glm::vec3, glm::vec3, glm::vec3);
	Property properties();
	glm::vec3 position();

private:
	
	glm::vec3 m_pos; 
	Box* m_box;
	Shader* m_shader;
	Property m_property;
};

