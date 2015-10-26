#pragma once

#include <vector>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

class ModelLoader
{
public:
	ModelLoader(const std::string filename);
	~ModelLoader(void);
	bool LoadMesh(const std::string filename);
	std::vector<Vertex> data();
	std::vector<unsigned int> indices();

private: 
	void InitFromScene(const aiScene* pScene, const std::string& filename);
	void InitMesh(const aiMesh* paiMesh);
	std::vector<Vertex> m_data; 
	std::vector<unsigned int> m_indices;
	bool m_hasTextures;
};

