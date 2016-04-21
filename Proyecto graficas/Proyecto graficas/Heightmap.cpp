#include "Heightmap.h"

void Heightmap::Draw( Shader shader )
{
//	glUniformMatrix4fv( glGetUniformLocation( shader.program, "localSpace" ), 1, GL_FALSE, glm::value_ptr( localSpace ) );
	mesh.Draw( shader );
}


void Heightmap::GenerateNewTerrain( GLuint seed, GLuint noiseSize, GLuint gridSize, GLfloat worldSize, GLfloat maxHeight )
{

	

	this->maxHeight = maxHeight;

	GLuint vertexCount = gridSize + 1;
	GLfloat quadSize = worldSize / gridSize;
	NoiseMap noiseMap( seed, noiseSize, vertexCount, vertexCount );

	mesh.vertices.clear();
	mesh.indices.clear();
	mesh.vertices.reserve( vertexCount * vertexCount );
	mesh.indices.reserve( gridSize * gridSize * 2 * 3);

	//std::vector<glm::vec3> normals;
	glm::vec3* normals = new glm::vec3[gridSize * gridSize * 2];
	//normals.reserve( gridSize * gridSize * 2 );

	int adsasd = 0;
	for ( int z = 0; z < vertexCount; z++ ) {
		for ( int x = 0; x < vertexCount; x++ ) {

			Vertex vert;

			vert.position.x = (GLfloat)x * quadSize;
			vert.position.y = noiseMap.noiseData[z*vertexCount + x] * maxHeight;
			vert.position.z = (GLfloat)z * quadSize;
			vert.normal = glm::vec3( 0.0f, 1.0f, 0.0f );
			vert.texCoord.x = (1 / vertexCount)*x;
			vert.texCoord.y = (1 / vertexCount)*z;

			mesh.vertices.push_back( vert );
		}
	}

	int index = 0;
	for ( GLuint z = 0; z < gridSize; z++ )
	{
		for ( GLuint x = 0; x < gridSize; x++ ) {

			GLuint start = z * vertexCount + x;
			glm::vec3 v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start].position);
			glm::vec3 v2 = (mesh.vertices[start + 1].position - mesh.vertices[start].position);
			//normals.push_back( glm::normalize( glm::cross( v1, v2 ) ) );
			normals[index++] = glm::normalize( glm::cross( v1, v2 ) );

			v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start + vertexCount + 1].position);
			v2 = (mesh.vertices[start + 1].position - mesh.vertices[start + vertexCount + 1].position);
			//normals.push_back( glm::normalize( glm::cross( v2, v1 ) ) );
			normals[index++] = glm::normalize( glm::cross( v2, v1 ) );

			mesh.indices.push_back( start );
			mesh.indices.push_back( start + vertexCount );
			mesh.indices.push_back( start + 1 );

			mesh.indices.push_back( start + 1 );
			mesh.indices.push_back( start + vertexCount );
			mesh.indices.push_back( start + vertexCount + 1 );

		}
	}

	int asdasddasasd = 0;
	for ( GLuint z = 0; z < gridSize - 1; z++ )
	{
		for ( GLuint x = 0; x < gridSize - 1; x++ ) {

			GLuint start = z * gridSize + x;
			glm::vec3 normalAverage;
			normalAverage += normals[start + 1];
			normalAverage += normals[start + 2];
			normalAverage += normals[start + 3];
			normalAverage += normals[start + gridSize];
			normalAverage += normals[start + gridSize + 1];
			normalAverage += normals[start + gridSize + 2];

			glm::normalize( normalAverage );

			GLuint vertexIndex = (z + 1) * vertexCount + (x + 1);
			mesh.vertices[vertexIndex].normal = normalAverage;
		}
	}

	delete normals;

	mesh.setupMesh();
}

void Heightmap::LoadTerrain(const GLchar* path, GLfloat maxHeight) {
	int width, height;
	//unsigned char* image = SOIL_load_image( "Textures//container.jpg", &width, &height, 0, SOIL_LOAD_RGB );
}

