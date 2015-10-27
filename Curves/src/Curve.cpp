#include "Curve.h"


Curve::Curve(int points)
{
	m_count = points;
	m_shader = nullptr;
	m_shader2 = nullptr;
	m_vbo = new VertexBufferObject();

}


Curve::~Curve(void){}

void Curve::setShader(Shader* shader)
{
	m_shader = shader;
}

void Curve::setShader(Shader* shader, Shader* shader2)
{
	m_shader = shader;
	m_shader2 = shader2;
}

void Curve::setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess)
{
	m_material.ka = a; 
	m_material.kd = d; 
	m_material.ks = s;
	m_material.shininess = shininess;
}

void Curve::init()
{
	float dt =  5 * M_PI / m_count;
	float t = 0; 
	for(int i = 0 ; i <= m_count; ++i)
	{
		t = dt * i;
		float x = 5.f * cosf(3.f * t);
		float y = 3.f*t - 3 * M_PI; 
		float z = 3.f * sinf(3.f * t);
		glm::vec3 p = glm::vec3(x,y,z);
		glm::vec2 t = glm::vec2(0);
		glm::vec3 n = glm::vec3(0);
		glm::vec3 c = glm::vec3(0.8f, 0.4f, 0.3f);

		Vertex d; 
		d.p = p;
		d.t = t;
		d.c = c;
		d.n = n;

		m_points.push_back(d);
		m_indices.push_back(i);
		
	}

	m_vbo->setIndices(m_indices);
	m_vbo->setVertexData(m_points);
	m_vbo->createBuffers();
	
}

void Curve::render(Camera* cam, std::vector<Light>& lights)
{
	if(m_shader!=nullptr)
	{
		glPointSize(10.f);
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
		glPointSize(1.f);
	}

	if(m_shader2!=nullptr)
	{
	
		glm::mat4 model = glm::translate(glm::mat4(1), m_position);
		model = glm::scale(model, glm::vec3(10, 10, 10));
		m_shader2->use();

		//MVP
		glm::mat4 m = cam->matrix() * model;
		//ModelViewMatrix
		glm::mat4 ModelViewMatrix = cam->view()*model;
		//NormalMatrix
		glm::mat3 NormalMatrix = glm::transpose(glm::inverse(glm::mat3(ModelViewMatrix)));

		m_shader2->setUniform("mvp", m);
		m_shader2->setUniform("ViewMatrix", cam->view());
		m_shader2->setUniform("NormalMatrix", NormalMatrix);
		m_shader2->setUniform("ModelViewMatrix", ModelViewMatrix);
		m_shader2->setUniform("EyePositionInWorld", cam->position());

		//Material
		m_shader2->setUniform("g_material.ka", m_material.ka);
		m_shader2->setUniform("g_material.kd", m_material.kd);
		m_shader2->setUniform("g_material.ks", m_material.ks);
		m_shader2->setUniform("g_material.shininess", m_material.shininess);

		for(unsigned int i = 0 ; i < lights.size(); i++)
		{
			std::string uniform_name = "g_light["+std::to_string(i)+"].";
			Light::Property p = lights[i].properties();
			m_shader2->setUniform(std::string(uniform_name+"position").c_str(), glm::vec4(lights[i].position(),1.f));
			m_shader2->setUniform(std::string(uniform_name+"la").c_str(), p.la);
			m_shader2->setUniform(std::string(uniform_name+"ld").c_str(), p.ld);
			m_shader2->setUniform(std::string(uniform_name+"ls").c_str(), p.ls);
		}

		//render mesh
		m_vbo->render(GL_LINE_STRIP_ADJACENCY);
		m_shader2->disuse();

	}
}