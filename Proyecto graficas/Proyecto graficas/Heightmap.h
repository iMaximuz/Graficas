#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_


#include "GameObject.h"
#include "Mesh.h"



class Heightmap : public GameObject{

	Mesh mesh;

	GLuint gridSize;
	GLfloat worldSize;
	GLuint worldSizeX;
	GLuint worldSizeZ;
	GLfloat maxHeight;

public:

	Heightmap( GLuint seed, GLuint noiseSize, GLuint gridSize, GLfloat worldSize, GLfloat maxHeight){

		this->gridSize = gridSize;
		this->worldSize = worldSize;
		this->maxHeight = maxHeight;
		this->worldSizeZ = this->worldSizeX = worldSize / 2;


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


	inline glm::vec2 GetWorldSize() {
		return glm::vec2( this->worldSizeX, this->worldSizeZ );
	}

};

#endif