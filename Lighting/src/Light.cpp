#include "Light.h"


Light::Light(glm::vec3 pos)
{
	m_pos = pos;
	m_shader = new Shader("shaders/LightVS.glsl", 
		                  "shaders/LightFS.glsl");
	m_box = new Box(1.f, m_pos, glm::vec3(1));
	m_box->setShader(m_shader);	
}

Light::~Light(void){}

void Light::setProperty(glm::vec3 la, glm::vec3 ld, glm::vec3 ls)
{
	m_property.la = la; 
	m_property.ld = ld; 
	m_property.ls = ls; 
}

Light::Property Light::properties()
{
	return m_property;
}

glm::vec3 Light::position()
{
	return m_pos;
}

void Light::render(Camera* cam)
{
	m_box->setPosition(m_pos);
	m_box->render(cam);
}
