#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_


#include "GameObject.h"
#include "Mesh.h"

struct HeightmapFile {
	GLint sizeX;
	GLint sizeY;
	GLfloat* data;
};

class Heightmap : public GameObject{

	Mesh mesh;

	GLuint gridSize;
	GLfloat worldSize;
	GLfloat maxHeight;

	MeshRenderMode renderMode;

public:



	Heightmap( GLuint seed, GLuint noiseSize, GLuint gridSize, GLfloat worldSize, GLfloat maxHeight){

		this->gridSize = gridSize;
		this->worldSize = worldSize;
		this->maxHeight = maxHeight;


		GenerateNewTerrain( seed, noiseSize, this->gridSize, this->worldSize, this->maxHeight );

	}

	Heightmap( const GLchar* path, GLfloat worldSize, GLfloat maxHeight ) {

		this->worldSize = worldSize;
		this->maxHeight = maxHeight;
		LoadTerrain( path, this->maxHeight );

	}

	void Render( Shader shader );

	void GenerateNewTerrain( GLuint seed, GLuint noiseSize, GLuint gridSize, GLfloat worldSize, GLfloat maxHeight );

	void LoadTerrain( const GLchar* path, GLfloat maxHeight );

	glm::vec3 CalculateHeigthColor ( GLfloat height );


	inline GLfloat GetWorldSize() {
		return this->worldSize;
	}

};

#endif