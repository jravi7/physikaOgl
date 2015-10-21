#pragma once


#include <gl/glew.h>
#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"

class Shader
{
public:
	Shader(const char* vsource, const char* fsource);
	~Shader(void);
	void use();   //use shader program
	void disuse();	//disable shader program
	void setUniform(const GLchar* name, glm::mat3 m);
	void setUniform(const GLchar* name, glm::mat4 m);
	void setUniform(const GLchar* name, glm::vec3);
	void setUniform(const GLchar* name, glm::vec4);
	void setSampler(const GLchar* name, GLushort unit);

private:
	char* file_read(const char* filename);
	GLuint createShader(GLenum shaderType, const char* fileData);
	void addVertexShader(const char* vfile);
	void addFragmentShader(const char* ffile);
	GLint getUniformLocation(const GLchar *varname);
	void compileProgram();
	void bindAttributeLocations();
	GLuint m_Program;
	GLuint m_vs;
	GLuint m_fs;

};

