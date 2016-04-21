#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "GameObject.h" 
#include "MathLib.h"
#include "Shader.h"
#include "Mesh.h"

class Sphere : public GameObject{

	Mesh mesh;

	GLfloat rad;
	GLfloat slices;
	GLfloat stacks;

	void GenerateSphere();

public:

	Sphere( GLfloat rad, GLfloat slices, GLfloat stacks );

	void Draw( Shader shader );


};

#endif