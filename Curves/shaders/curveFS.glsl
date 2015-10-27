#version 330

#define LIGHT_COUNT 1
struct Light
{
	vec3 la; 
	vec3 ld; 
	vec3 ls;
	vec4 position; 
};

struct Material
{
	vec3 ka; 
	vec3 kd; 
	vec3 ks;
	float shininess;
};

//In Variables
in vec3 fVertexColor;
in vec3 fVertexNormal; 
in vec2 fVertexTexture; 
in vec3 fVertexPosition;

//Uniforms
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;

uniform vec3 EyePositionInWorld;

uniform Light	 g_light[LIGHT_COUNT]; 
uniform Material g_material;

uniform sampler2D TextureSample2D;

//Out Variables
out vec4 outputColor;

vec4 phongDA(Light light, vec3 surface_normal)
{
	vec4 VertexEyeCoords = ModelViewMatrix * vec4(fVertexPosition, 1.0); 
	vec4 lightEye = ViewMatrix * light.position;
	vec3 lightVector = normalize(vec3(lightEye - VertexEyeCoords));
	
	float sdotn = max(dot(lightVector, surface_normal), 0.0);

	vec3 diffuse = light.ld * g_material.kd * sdotn; 
	vec3 ambient = light.la * g_material.ka;

	outputColor = vec4(diffuse, 1.f);

	return outputColor;
}

vec4 phongS(Light light, vec3 surface_normal)
{
	vec4 VertexEyeCoords = ModelViewMatrix * vec4(fVertexPosition, 1.0); 
	vec4 lightEye = ViewMatrix * light.position;
	vec3 lightVector = normalize(vec3(lightEye - VertexEyeCoords));

	//Reflect vector
	vec3 r = reflect(-lightVector, surface_normal);
	vec3 v = normalize(EyePositionInWorld-VertexEyeCoords.xyz);

	vec3 specular = vec3(0);

	float sdotn = max(dot(lightVector, surface_normal), 0.0);

	if(sdotn > 0.0)
		specular = light.ls*g_material.ks*pow(max(dot(r,v),0.0),g_material.shininess);
	
	outputColor = vec4(specular,1);

	return outputColor;
}


void main()
{		
		
	//Surface normal vector
	vec3 tnorm = normalize(vec3(NormalMatrix * fVertexNormal));
	vec4 resultDA = vec4(g_light[0].la*g_material.ka,1);
	vec4 resultS = vec4(0);
	vec4 point_color = vec4(0.545f, 0.27f, 0.074f,1.f);

	vec4 TexColor = texture(TextureSample2D, fVertexTexture);
	for(int i = 0; i < LIGHT_COUNT; i++)
	{
	//	resultDA += phongDA(g_light[i], tnorm);
	//	resultS  += phongS(g_light[i], tnorm);
	}
	//outputColor = (resultDA*point_color) + resultS;
	
	outputColor = vec4(fVertexColor,1.f);
}
