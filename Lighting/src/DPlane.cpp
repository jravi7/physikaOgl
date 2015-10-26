#include "DPlane.h"


DPlane::DPlane(	glm::vec3 pos,
				glm::vec3 color,
				int side,
				int cs)
{
	m_pos = pos;
	m_cs = cs;
	m_side = side;
	m_color = color;
	m_vbo = new VertexBufferObject();
	init();
	m_shader = nullptr;
	

}

DPlane::~DPlane(void){}

void DPlane::setShader(Shader* shader)
{
	m_shader = shader;
}

void DPlane::setMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shininess)
{
	m_material.ka = a;
	m_material.kd = d;
	m_material.ks = s;
	m_material.shininess = shininess;
}

void DPlane::setTexture(Texture* texture)
{
	m_texture = texture;
}

void DPlane::init()
{
	std::vector<glm::vec3> verts; 
	std::vector<glm::vec2> tcoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors; 

	for(int j = 0; j < m_side; j++)
	{
		for(int i = 0; i < m_side; i++)
		{
			glm::vec3 v = glm::vec3(i*m_cs, 0, -j*m_cs);
			glm::vec3 c = m_color;
			glm::vec2 t = 4.f * glm::vec2(v.x/m_side, v.z/m_side);
			colors.push_back(c);
			verts.push_back(v);
			tcoords.push_back(t);
		}
	}

	//create indices for the grid
	for( unsigned int j = 0; j < m_side-1 ; j++)
	{

		for( unsigned int i = 0; i < m_side-1; i++)
		{
			unsigned int v1 = i + j*m_side;
			unsigned int v2 = (i + 1) + j*m_side;
			unsigned int v6 = i+ (j+1)*m_side;
			unsigned int v7 = (i+1)+((j+1)*m_side);

			//CCW
			m_indices.push_back(v1);
			m_indices.push_back(v2);
			m_indices.push_back(v6);
			
			m_indices.push_back(v2);
			m_indices.push_back(v7);
			m_indices.push_back(v6);
			
		}
	}


	//initialize m_normals
	for(int i = 0 ; i < verts.size();i++)
	{
		normals.push_back(glm::vec3(0,0,0));
	}

	//This works for row wise grids 
	//Make sure the grid is row wise else the normals are going to be incorrect. 
	for(int i = 0; i < m_indices.size();i+=3)
	{
		unsigned int idx1 = m_indices[i];
		unsigned int idx2 = m_indices[i+1];
		unsigned int idx3 = m_indices[i+2];

		glm::vec3 A = verts[idx1];
		glm::vec3 B = verts[idx2];
		glm::vec3 C = verts[idx3];

		glm::vec3 AB = B-A; 
		glm::vec3 AC = C-A; 
		glm::vec3 cross = glm::cross(AB, AC);

		normals[idx1] += cross;
		normals[idx2] += cross;
		normals[idx3] += cross;

	}

	for(int i = 0 ; i < verts.size();i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}

	assert(verts.size()==normals.size());
	assert(verts.size()==tcoords.size());
	assert(verts.size()==colors.size());

	for(int i = 0; i < verts.size(); i++)
	{
		Vertex v; 
		v.p = verts[i];
		v.t = tcoords[i];
		v.n = normals[i];
		v.c = colors[i];
		m_data.push_back(v);
	}
	
	m_vbo->setVertexData(m_data);
	m_vbo->setIndices(m_indices);
	m_vbo->createBuffers();
}

void DPlane::render(Camera* cam, std::vector<Light>& lights)
{
	if(m_shader != nullptr)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), m_pos);
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
		
		m_texture->activate(GL_TEXTURE0);
		m_shader->setSampler("TextureSample2D", 0);

		for(unsigned int i = 0 ; i < lights.size(); i++)
		{
			std::string uniform_name = "g_light["+std::to_string(i)+"].";
			Light::Property p = lights[i].properties();
			m_shader->setUniform(std::string(uniform_name+"position").c_str(), glm::vec4(lights[i].position(),1.f));
			m_shader->setUniform(std::string(uniform_name+"la").c_str(), p.la);
			m_shader->setUniform(std::string(uniform_name+"ld").c_str(), p.ld);
			m_shader->setUniform(std::string(uniform_name+"ls").c_str(), p.ls);
		}
		m_vbo->render(GL_TRIANGLES);
		m_texture->deactivate();
		m_shader->disuse();
	}
}