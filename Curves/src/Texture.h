#pragma once

//C++
#include <string>

//3rd Party
#include <GL\glew.h>

//physika
#include "ImageIO.h"

class Texture
{
public:
	Texture(GLenum texture_target);
	~Texture(void);

	void init();
	void init2d();
	void init3d();
	void activate(GLenum texture_unit); 
	void deactivate(); 

	void setWrap(GLint); 
	void setImagePath(std::string file);
	void setMinFilter(GLfloat min); 
	void setMagFilter(GLfloat mag);

private: 

	GLint   m_wrap; 
	GLuint  m_texture_id; 
	GLenum  m_texture_target; 

	GLfloat m_min_filter; 
	GLfloat m_mag_filter; 

	std::string m_file; 

};

