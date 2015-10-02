#version 330

//In variables

in vec3 fVertexColor;

//Out Variables

out vec4 out_color; 


void main()
{
	out_color = vec4(fVertexColor,1);
}