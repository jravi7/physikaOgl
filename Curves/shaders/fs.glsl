#version 330

//In variables
in vec3 fVertexPosition;
in vec3 fVertexNormal;

//Out Variables

out vec4 fVertexColor; 


uniform mat4 ModelView; 

void main()
{

	//vec4 eyeCoords = ModelView * vec4(fVertexPosition, 1.0);
	//vec3 lightPos = vec3(10, 50, -100);
	//vec3 lightDir = normalize(lightPos - vec3(eyeCoords));
	vec3 lightDir = normalize(vec3(0.0, -1.0, 0.0));
	vec3 norm = normalize(fVertexNormal);

	vec3 ka = vec3(0.5);
	vec3 la = vec3(0.5);

	vec3 kd = vec3(1);
	vec3 ld = vec3(1.0);

	vec3 ambient = ka * la;
	vec3 diffuse = kd*ld*max(dot(norm, -lightDir), 0.0); 
	//vec3 diffuse = vec3(1.0);
	vec3 objectColor = vec3(0,.9,0.5);
	fVertexColor = vec4(objectColor*ambient*diffuse,1);
}