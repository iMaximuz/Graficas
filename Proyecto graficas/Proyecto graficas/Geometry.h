#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Precompiled.h"
#include "Mesh.h"
#include "GameObject.h"

//TODO: Crear clase para almacenar solo la informacion de una esfera para su modificacion

class SphereData {

	

};

class Sphere : public GameObject{

	Mesh mesh;

	GLfloat rad;
	GLfloat slices;
	GLfloat stacks;

	void GenerateSphere();

	MeshRenderMode renderMode;

public:

	Sphere( GLfloat rad, GLfloat slices, GLfloat stacks, MeshRenderMode mode );

	void Render( Shader shader );
	void Update( GLfloat dt );

};

#endif