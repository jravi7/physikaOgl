#version 330

//In variables
in vec3 VertexPosition; 
in vec3 VertexNormal;

//Out Variables
out vec3 fVertexPosition;
out vec3 fVertexNormal;

//Matrices
uniform mat4 mvp;

void main()
{
	fVertexPosition = VertexPosition; 
	fVertexNormal   = VertexNormal; 
	gl_Position =	mvp * vec4(VertexPosition, 1.0f);
}