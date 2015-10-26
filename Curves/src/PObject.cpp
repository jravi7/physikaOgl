#include "PObject.h"


PObject::PObject(glm::vec3 position, std::string file)
{
	m_position = position;
	m_loader = new ModelLoader(file);
	m_vbo = new VertexBufferObject();
	m_vbo->setVertexData(m_loader->data());
	m_vbo->setIndices(m_loader->indices());
	m_vbo->createBuffers();
}

PObject::~PObject(void){}

void PObject::setShader(Shader* shader)
{
	m_shader = shader; 
}

void PObject::setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess)
{
	m_material.ka = a; 
	m_material.kd = d;
	m_material.ks = s;
	m_material.shininess = shininess;
}

void PObject::render(Camera* cam, std::vector<Light>& lights)
{
	if(m_shader!=nullptr)
	{
		
		glm::mat4 model = glm::translate(glm::mat4(1), m_position);
		model = glm::scale(model, glm::vec3(10, 10, 10));
		m_shader->use();

		//MVP
		glm::mat4 m = cam->matrix() * model;
		//ModelViewMatrix
		glm::mat4 ModelViewMatrix = cam->view()*model;
		//NormalMatrix
		glm::mat3 NormalMatrix = glm::transpose(glm::inverse(glm::mat3(ModelViewMatrix)));

		m_shader->setUniform("mvp", m);
		m_shader->setUniform("ViewMatrix", cam->view());
		m_shader->setUniform("NormalMatrix", NormalMatrix);
		m_shader->setUniform("ModelViewMatrix", ModelViewMatrix);
		m_shader->setUniform("EyePositionInWorld", cam->position());

		//Material
		m_shader->setUniform("g_material.ka", m_material.ka);
		m_shader->setUniform("g_material.kd", m_material.kd);
		m_shader->setUniform("g_material.ks", m_material.ks);
		m_shader->setUniform("g_material.shininess", m_material.shininess);

		for(unsigned int i = 0 ; i < lights.size(); i++)
		{
			std::string uniform_name = "g_light["+std::to_string(i)+"].";
			Light::Property p = lights[i].properties();
			m_shader->setUniform(std::string(uniform_name+"position").c_str(), glm::vec4(lights[i].position(),1.f));
			m_shader->setUniform(std::string(uniform_name+"la").c_str(), p.la);
			m_shader->setUniform(std::string(uniform_name+"ld").c_str(), p.ld);
			m_shader->setUniform(std::string(uniform_name+"ls").c_str(), p.ls);
		}

		//render mesh
		m_vbo->render(GL_POINTS);
		m_shader->disuse();
	}
}

