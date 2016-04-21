#include "Geometry.h"

//TODO: Quitar el radio de la esfera, la esfera debe ser unitaria.
Sphere::Sphere( GLfloat rad, GLfloat slices, GLfloat stacks )
{
	this->rad = rad;
	this->slices = slices;
	this->stacks = stacks;
	GenerateSphere();
}

void Sphere::GenerateSphere()
{
	for ( int i = 0; i < slices; i++ ) {
		for ( int j = 0; j < stacks; j++ ) {

			GLfloat theta = i*PI *2 / slices;
			GLfloat phi = j*PI / stacks;

			Vertex vert;

			//TODO: Acomodar el orden correcto
			vert.position.x = rad * (cosf( theta )* sinf( phi ));
			vert.position.y = rad * sinf( theta )* sinf( phi );
			vert.position.z = rad * cosf( phi );

			mesh.vertices.push_back( vert );

		}
	}

	//TODO: Calcular Indices

}


void Sphere::Draw( Shader shader )
{
//	glUniformMatrix4fv( glGetUniformLocation( shader.program, "localSpace" ), 1, GL_FALSE, glm::value_ptr( localSpace ) );
	mesh.Draw( shader );
}
