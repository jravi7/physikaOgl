#version 330

//In variables
in vec3 fVertexPosition;
in vec3 fVertexNormal;
in vec3 fVertexColor;

//Out Variables

out vec4 final_color; 


void main()
{	
	final_color = vec4(fVertexColor,1);
}