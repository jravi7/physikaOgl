#include "DPlane.h"


DPlane::DPlane(glm::vec3 pos, 
		   int side,
		   int cs)
{
	m_pos = pos;
	m_cs = cs;
	m_side = side;
	m_vbo = new VertexBufferObject();
	init();

}

DPlane::~DPlane(void){}

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

void DPlane::render(Shader* shader)
{
	m_vbo->render(GL_TRIANGLES);
}