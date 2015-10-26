//Author: Jay Ravi
//Date: Oct 21st 2015

#pragma once

//Bind Locations
#define VERTEX_POSITION		0
#define VERTEX_NORMAL		1
#define VERTEX_TEXTURE		2
#define VERTEX_COLOR		3

//3rd Party
#include <glm\glm.hpp>

//physika
#include "Texture.h"

struct Vertex
{
	glm::vec3 p; 
	glm::vec2 t; 
	glm::vec3 n;
	glm::vec3 c;

	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal, const glm::vec3& color)
	{
		p    = pos;
		t    = tex;
		n	 = normal;
		c	 = color;
	}
};

struct Material
{
	glm::vec3 ka; 
	glm::vec3 kd; 
	glm::vec3 ks;
	Texture*  kdTex; 
	Texture*  ksTex;
	float shininess;
};