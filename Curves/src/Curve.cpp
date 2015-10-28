#include "Curve.h"


Curve::Curve(int points)
{
	m_count = points;
	m_shader = nullptr;
	m_shader2 = nullptr;
	m_vbo = new VertexBufferObject();
	m_vbo2 = new VertexBufferObject();
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
	int circle_count = 50;
	std::vector<glm::vec3> curve_points; 
	std::vector<glm::vec3> circle_points;
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
		
		curve_points.push_back(p);
		m_points.push_back(d);
		m_indices.push_back(i);
	}
	m_vbo->setIndices(m_indices);
	m_vbo->setVertexData(m_points);
	m_vbo->createBuffers();

	dt = 2*M_PI / circle_count ;
	for(int i = 1 ; i < curve_points.size()-1 ; i++)
	{
		glm::mat4 R(1.f);
		glm::mat4 T(1.f);

		glm::vec3 pointback = curve_points[i-1];
		glm::vec3 pointmid = curve_points[i];
		glm::vec3 pointforward = curve_points[i+1];

		glm::vec3 forward_tangent_vector =  glm::vec3(glm::normalize(pointforward - pointmid)) ;
		glm::vec3 backward_tangent_vector = glm::vec3(glm::normalize(pointmid - pointback)) ;

		glm::vec3 second_order_tangent = glm::normalize(forward_tangent_vector - backward_tangent_vector);

		glm::vec3 binormal = glm::normalize(glm::cross(forward_tangent_vector, second_order_tangent));

		glm::vec3 normal = glm::normalize(glm::cross(binormal, forward_tangent_vector));

		glm::mat3 tbn = glm::mat3(forward_tangent_vector,binormal,normal);

		glm::vec3 normal_axis = glm::vec3(0, 1, 0);
		//normal_axis = forward_tangent_vector;

		glm::vec3 circleNormal = glm::normalize(tbn * normal_axis);
		glm::vec3 rotationAxis = glm::cross(normal_axis, circleNormal);
		float rotationAngle = glm::acos(glm::dot(normal_axis, circleNormal));

		R = glm::rotate(R, glm::degrees(rotationAngle), rotationAxis);

		T = glm::translate(T, pointmid);

		glm::mat4 M = T*R;
		

		
		for(int i = 0 ; i < circle_count ; i++)
		{
			float x = 0.1f*cos(dt * i);
			float z = 0.f;
			float y = 0.1f*sin(dt * i);;

			glm::vec4 p = M * glm::vec4(x, y, z, 1);
			circle_points.push_back(glm::vec3(p));
		}

	}

	for(int i = 0 ; i < circle_points.size(); i++)
	{
		glm::vec3 p = circle_points[i];
		glm::vec2 t = glm::vec2(0);
		glm::vec3 n = glm::vec3(0);
		glm::vec3 c = glm::vec3(0.8f, 0.4f, 0.3f);
		
		Vertex d; 
		d.p = p;
		d.t = t;
		d.c = c;
		d.n = n;
		
		m_circle_points.push_back(d);
		m_indices2.push_back(i);
	}


	m_vbo2->setIndices(m_indices2);
	m_vbo2->setVertexData(m_circle_points);
	m_vbo2->createBuffers();
	
}

void Curve::render(Camera* cam, std::vector<Light>& lights)
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
		m_vbo2->render();
		m_shader->disuse();
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