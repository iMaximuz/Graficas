#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Precompiled.h"
#include "Mesh.h"
#include "GameObject.h"

class Sphere : public GameObject{

	Mesh mesh;

	GLfloat rad;
	GLfloat slices;
	GLfloat stacks;

	void GenerateSphere();

public:

	Sphere( GLfloat rad, GLfloat slices, GLfloat stacks );

	void Render( Shader shader );


};

#endif