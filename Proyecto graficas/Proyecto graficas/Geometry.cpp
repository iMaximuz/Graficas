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
	GLint vertexCount = stacks + 1;


	//TODO: Calcular normales por cara
	glm::vec3* normals = new glm::vec3[(slices + 1) * (stacks + 1) * 2];

	for ( int z = 0; z < slices + 1; z++ ) {
		for ( int x = 0; x < stacks + 1; x++ ) {

			Vertex vert;

			GLfloat theta = z*PI *2 / slices;
			GLfloat phi = x*PI / stacks;


			//TODO: Acomodar el orden correcto
			vert.position.x = rad * cosf( theta )* sinf( phi );
			vert.position.y = rad * cosf( phi );
			vert.position.z = rad * sinf( theta )* sinf( phi );
			vert.normal = glm::vec3( 0.0f, 1.0f, 0.0f );
			vert.texCoord.x = (1 / vertexCount)*x;
			vert.texCoord.y = (1 / vertexCount)*z;

			mesh.vertices.push_back( vert );

		}
	}

	int index = 0;

	
	for ( int z = 0; z < slices; z++ ) {
		for ( int x = 0; x < stacks; x++ ) {


			GLuint start = z * vertexCount + x;
			glm::vec3 v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start].position);
			glm::vec3 v2 = (mesh.vertices[start + 1].position - mesh.vertices[start].position);
			//normals.push_back( glm::normalize( glm::cross( v1, v2 ) ) );
			normals[index++] = glm::normalize( glm::cross( v1, v2 ) );

			v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start + vertexCount + 1].position);
			v2 = (mesh.vertices[start + 1].position - mesh.vertices[start + vertexCount + 1].position);
			//normals.push_back( glm::normalize( glm::cross( v2, v1 ) ) );
			normals[index++] = glm::normalize( glm::cross( v2, v1 ) );


			//mesh.vertices[vertexIndex].normal = normalAverage;

			mesh.indices.push_back( start );
			mesh.indices.push_back( start + vertexCount );
			mesh.indices.push_back( start + 1 );

			mesh.indices.push_back( start + 1 );
			mesh.indices.push_back( start + vertexCount );
			mesh.indices.push_back( start + vertexCount + 1 );


		}
	}

	for ( GLuint z = 0; z < slices; z++ )
	{
		for ( GLuint x = 0; x < stacks; x++ ) {

			GLuint start = z * stacks + x;
			glm::vec3 normalAverage;
			normalAverage += normals[start + 1];
			normalAverage += normals[start + 2];
			normalAverage += normals[start + 3];
			normalAverage += normals[start + (int)stacks];
			normalAverage += normals[start + (int)stacks + 1];
			normalAverage += normals[start + (int)stacks + 2];

			glm::normalize( normalAverage );

			GLuint vertexIndex = (z + 1) * (vertexCount)+(x + 1);
			mesh.vertices[vertexIndex].normal = normalAverage;
		}
	}


	delete normals;

	mesh.setupMesh();

}


void Sphere::Render( Shader shader )
{
	glUniformMatrix4fv( glGetUniformLocation( shader.program, "model" ), 1, GL_FALSE, glm::value_ptr( this->transform.GetWorldMatrix() ) );
	mesh.Draw( shader );
}
