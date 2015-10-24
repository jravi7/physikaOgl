//Physika X 
//Author: Jay Ravi
//Date: Oct 1st, 2015

#include "Box.h"


Box::Box(int side, glm::vec3 position, glm::vec3 color)
{
	m_side = side; 
	m_position = position; 
	m_color = color;
	m_vbo = new VertexBufferObject();
	m_shader = nullptr;
	createCube();
	fillBuffers();
}

Box::~Box(void){}

void Box::setShader(Shader* shader)
{
	m_shader = shader;
}
void Box::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

void Box::setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess)
{
	m_material.ka = a;
	m_material.kd = d;
	m_material.ks = s;
	m_material.shininess = shininess;
}

unsigned int Box::addVertexData(glm::vec3 p, glm::vec3 n)
{
	Vertex v; 
	v.p = p;
	v.t = glm::vec2((p.x+m_side*0.5f)/m_side, (p.y+m_side*0.5f)/m_side);
	v.n = n;
	v.c = m_color;

	m_vertex_data.push_back(v);
	return m_vertex_data.size()-1;
}

void Box::addFace(unsigned int v1, unsigned int v2, unsigned int v3)
{
	m_indices.push_back(v1);
	m_indices.push_back(v2);
	m_indices.push_back(v3);
}

void Box::createCube()
{
	glm::vec3 v1( m_side*0.5f,  m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v2(-m_side*0.5f,  m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v3(-m_side*0.5f, -m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v4( m_side*0.5f, -m_side*0.5f,  m_side*0.5f); 
	glm::vec3 v5( m_side*0.5f,  m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v6(-m_side*0.5f,  m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v7(-m_side*0.5f, -m_side*0.5f, -m_side*0.5f); 
	glm::vec3 v8( m_side*0.5f, -m_side*0.5f, -m_side*0.5f);

	unsigned int i1 = addVertexData(v1, glm::normalize(v1/3.f));
	unsigned int i2 = addVertexData(v2, glm::normalize(v2/3.f));
	unsigned int i3 = addVertexData(v3, glm::normalize(v3/3.f));
	unsigned int i4 = addVertexData(v4, glm::normalize(v4/3.f));
	unsigned int i5 = addVertexData(v5, glm::normalize(v5/3.f));
	unsigned int i6 = addVertexData(v6, glm::normalize(v6/3.f));
	unsigned int i7 = addVertexData(v7, glm::normalize(v7/3.f));
	unsigned int i8 = addVertexData(v8, glm::normalize(v8/3.f));

	//front
	addFace(i1, i2, i3);
	addFace(i1, i3, i4);

	//top

	addFace(i5, i6, i2);
	addFace(i5, i2, i1);

	//right

	addFace(i5, i1, i4);
	addFace(i5, i4, i8);

	//back
	addFace(i6, i5, i8);
	addFace(i6, i8, i7);

	//left
	addFace(i2, i6, i7);
	addFace(i2, i7, i3);


	//bottom
	addFace(i4, i3, i7);
	addFace(i4, i7, i8);
}

void Box::fillBuffers()
{
	m_vbo->setVertexData(m_vertex_data);
	m_vbo->setIndices(m_indices);
	m_vbo->createBuffers();
}

void Box::render(Camera* cam, std::vector<Light>& lights)
{
	if(m_shader!=nullptr)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), m_position);
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
		m_vbo->render(GL_TRIANGLES);
		m_shader->disuse();
	}
}

void Box::render(Camera* cam)
{
	if(m_shader!=nullptr)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), m_position);
		m_shader->use();

		//MVP
		glm::mat4 m = cam->matrix() * model;
		
		m_shader->setUniform("mvp", m);
		
		//render mesh
		m_vbo->render(GL_TRIANGLES);
		m_shader->disuse();
	}
}