#version 330

//In variables
in vec3 VertexPosition; 
in vec3 VertexNormal;

//Out Variables
out vec3 fVertexPosition;
out vec3 fVertexColor;

//Matrices
uniform mat4 mvp[200];

//Colors
uniform vec3 cubeColor[200];
void main()
{
	fVertexPosition = VertexPosition;
	fVertexColor = cubeColor[gl_InstanceID];
	gl_Position =	mvp[gl_InstanceID] * vec4(VertexPosition, 1.0f);
}