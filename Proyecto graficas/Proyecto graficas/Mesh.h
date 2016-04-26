#ifndef _MESH_H_
#define _MESH_H_
#include <iostream>
#include <sstream>
#include <string>
//#include <glew.h>
#include <vector>
#include "MathLib.h"

#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCoord;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

enum MeshRenderMode{
	Mesh_Arrays,
	Mesh_Element
};

class Mesh {

	GLuint VBO, EBO, VAO;
	MeshRenderMode renderMode;

public:
	
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	void setupMesh(MeshRenderMode mode);

	Mesh();
	Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures );
	~Mesh();
	void Draw( Shader shader );
	inline void SetRenderMode(MeshRenderMode mode) { this->renderMode = mode; }
};

#endif