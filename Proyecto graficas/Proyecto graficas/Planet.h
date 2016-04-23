#ifndef _PLANET_H_
#define _PLANET_H_

#include "Precompiled.h"
#include "Mesh.h"
#include "GameObject.h"

class Planet : public GameObject {

	Mesh mesh;

	GLfloat maxRad;
	GLfloat slices;
	GLfloat stacks;

	void GeneratePlanet(GLuint seed, GLuint noiseSize );

public:

	Planet() {}
	Planet( GLfloat maxRad, GLfloat slices, GLfloat stacks, GLuint seed, GLuint noiseSize );

	void GenerateNewPlanet( GLfloat maxRad, GLfloat slices, GLfloat stacks, GLuint seed, GLuint noiseSize );

	void Render( Shader shader );

};


#endif // !_PLANET_H_
