#include "Heightmap.h"
#include "NoiseMap.h"

#define COLORBYTE(x) (GLfloat)x / 255.0f

void Heightmap::Render( Shader shader )
{

	/*
	uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
	*/
	glUniformMatrix4fv( glGetUniformLocation( shader.program, "model" ), 1, GL_FALSE, glm::value_ptr( this->transform.GetWorldMatrix() ) );
	mesh.Draw( shader );
}


void Heightmap::GenerateNewTerrain( GLuint seed, GLuint noiseSize, GLuint gridSize, GLfloat worldSize, GLfloat maxHeight )
{
	this->renderMode = Mesh_Arrays;
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

	if (this->renderMode == Mesh_Element) {

		for (int z = 0; z < vertexCount; z++) {
			for (int x = 0; x < vertexCount; x++) {

				Vertex vert;

				vert.position.x = (GLfloat)x * quadSize;
				vert.position.y = noiseMap.noiseData[z*vertexCount + x] * maxHeight;
				vert.position.z = (GLfloat)z * quadSize;
				vert.normal = glm::vec3(0.0f, 1.0f, 0.0f);
				vert.texCoord.x = (1 / vertexCount)*x;
				vert.texCoord.y = (1 / vertexCount)*z;
				vert.color = glm::vec3 ( 1.0f, 1.0f, 1.0f );
				mesh.vertices.push_back(vert);
			}
		}

		int index = 0;
		for (GLuint z = 0; z < gridSize; z++)
		{
			for (GLuint x = 0; x < gridSize; x++) {

				GLuint start = z * vertexCount + x;
				glm::vec3 v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start].position);
				glm::vec3 v2 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start + 1].position);
				//normals.push_back( glm::normalize( glm::cross( v1, v2 ) ) );
				normals[index++] = glm::normalize(glm::cross(v2, v1));

				v1 = (mesh.vertices[start + vertexCount + 1].position - mesh.vertices[start + 1].position);
				v2 = (mesh.vertices[start + vertexCount + 1].position - mesh.vertices[start + vertexCount].position);
				//normals.push_back( glm::normalize( glm::cross( v2, v1 ) ) );
				normals[index++] = glm::normalize(glm::cross(v1, v2));

				mesh.indices.push_back(start);
				mesh.indices.push_back(start + vertexCount);
				mesh.indices.push_back(start + 1);

				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + vertexCount);
				mesh.indices.push_back(start + vertexCount + 1);

			}
		}


		for (GLuint z = 0; z < gridSize - 1; z++)
		{
			for (GLuint x = 0; x < gridSize - 1; x++) {

				GLuint start = z * gridSize + x;
				glm::vec3 normalAverage;
				normalAverage += normals[start + 1];
				normalAverage += normals[start + 2];
				normalAverage += normals[start + 3];
				normalAverage += normals[start + gridSize];
				normalAverage += normals[start + gridSize + 1];
				normalAverage += normals[start + gridSize + 2];

				glm::normalize(normalAverage);

				GLuint vertexIndex = (z + 1) * vertexCount + (x + 1);
				mesh.vertices[vertexIndex].normal = normalAverage;
			}
		}
	}
	else if (this->renderMode == Mesh_Arrays) {

		for (int z = 0; z < gridSize; z++) {
			for (int x = 0; x < gridSize; x++) {

				Vertex vert[3];

				vert[0].position.x = (GLfloat)x * quadSize;
				vert[0].position.y = noiseMap.noiseData[z * vertexCount + x] * maxHeight;
				vert[0].position.z = (GLfloat)z * quadSize;
				vert[0].texCoord.x = (1 / vertexCount)*x;
				vert[0].texCoord.y = (1 / vertexCount)*z;

				vert[1].position.x = (GLfloat)x * quadSize;
				vert[1].position.y = noiseMap.noiseData[(z + 1) * vertexCount + x] * maxHeight;
				vert[1].position.z = (GLfloat)(z + 1) * quadSize;
				vert[1].texCoord.x = (1 / vertexCount)*x;
				vert[1].texCoord.y = (1 / vertexCount) * (z + 1);

				vert[2].position.x = (GLfloat)(x + 1) * quadSize;
				vert[2].position.y = noiseMap.noiseData[z * vertexCount + (x + 1)] * maxHeight;
				vert[2].position.z = (GLfloat)z * quadSize;
				vert[2].texCoord.x = (1 / vertexCount) * (x + 1);
				vert[2].texCoord.y = (1 / vertexCount)*z;

				glm::vec3 v1 = vert[1].position - vert[0].position;
				glm::vec3 v2 = vert[1].position - vert[2].position;

				glm::vec3 normal = glm::cross(v2, v1);

				GLfloat averageHeight = (vert[0].position.y + vert[1].position.y + vert[2].position.y) / 3;
				GLfloat totalHeight = myMath::MapValue ( averageHeight, 0, maxHeight, 0, 100 );
				glm::vec3 finalColor = CalculateHeigthColor ( totalHeight );


				vert[0].normal = normal;
				vert[1].normal = normal;
				vert[2].normal = normal;

#if 0
				vert[0].color = finalColor;
				vert[1].color = finalColor;
				vert[2].color = finalColor;

#else

				vert[0].color = CalculateHeigthColor( myMath::MapValue( vert[0].position.y, 0, maxHeight, 0, 100 ));//finalColor;
				vert[1].color = CalculateHeigthColor( myMath::MapValue( vert[1].position.y, 0, maxHeight, 0, 100 ));//finalColor;
				vert[2].color = CalculateHeigthColor( myMath::MapValue( vert[2].position.y, 0, maxHeight, 0, 100 ));//finalColor;

#endif
				mesh.vertices.push_back(vert[0]);
				mesh.vertices.push_back(vert[1]);
				mesh.vertices.push_back(vert[2]);

				vert[0].position.x = (GLfloat)(x + 1) * quadSize;
				vert[0].position.y = noiseMap.noiseData[z * vertexCount + (x + 1)] * maxHeight;
				vert[0].position.z = (GLfloat)z * quadSize;
				vert[0].texCoord.x = (1 / vertexCount) * (x + 1);
				vert[0].texCoord.y = (1 / vertexCount)*z;

				vert[1].position.x = (GLfloat)x * quadSize;
				vert[1].position.y = noiseMap.noiseData[(z + 1) * vertexCount + x] * maxHeight;
				vert[1].position.z = (GLfloat)(z + 1) * quadSize;
				vert[1].texCoord.x = (1 / vertexCount) * x;
				vert[1].texCoord.y = (1 / vertexCount) * (z + 1);

				vert[2].position.x = (GLfloat)(x + 1) * quadSize;
				vert[2].position.y = noiseMap.noiseData[(z + 1) * vertexCount + (x + 1)] * maxHeight;
				vert[2].position.z = (GLfloat)(z + 1) * quadSize;
				vert[2].texCoord.x = (1 / vertexCount) * (x + 1);
				vert[2].texCoord.y = (1 / vertexCount) * (z + 1);

				v1 = vert[2].position - vert[0].position;
				v2 = vert[2].position - vert[1].position;

				normal = glm::cross(v1, v2);

				averageHeight = (vert[0].position.y + vert[1].position.y + vert[2].position.y) / 3;
				totalHeight = myMath::MapValue ( averageHeight, 0, maxHeight, 0, 100 );
				finalColor = CalculateHeigthColor ( totalHeight );


				vert[0].normal = normal;
				vert[1].normal = normal;
				vert[2].normal = normal;


#if 0
				vert[0].color = finalColor;
				vert[1].color = finalColor;
				vert[2].color = finalColor;

#else

				vert[0].color = CalculateHeigthColor( myMath::MapValue( vert[0].position.y, 0, maxHeight, 0, 100 ) );
				vert[1].color = CalculateHeigthColor( myMath::MapValue( vert[1].position.y, 0, maxHeight, 0, 100 ) );
				vert[2].color = CalculateHeigthColor( myMath::MapValue( vert[2].position.y, 0, maxHeight, 0, 100 ) );

#endif

				mesh.vertices.push_back(vert[0]);
				mesh.vertices.push_back(vert[1]);
				mesh.vertices.push_back(vert[2]);
			}
		}

	}
	delete normals;

	mesh.setupMesh(this->renderMode);
}

void Heightmap::LoadTerrain(const GLchar* path, GLfloat maxHeight) {
	int width, height;
	//unsigned char* image = SOIL_load_image( "Textures//container.jpg", &width, &height, 0, SOIL_LOAD_RGB );
}


glm::vec3 Heightmap::CalculateHeigthColor( GLfloat height ){

	glm::vec3 result;

	if (height <= 15) result = glm::vec3 ( COLORBYTE(255), 0.0f, 0.0f );
	else if ( height <= 20 ) result = glm::vec3( COLORBYTE( 80 ), COLORBYTE( 54 ), COLORBYTE( 3 ) );
	else if ( height <= 30 ) result = glm::vec3( COLORBYTE( 105 ), COLORBYTE( 54 ), COLORBYTE( 3 ) );
	else if ( height <= 40 ) result = glm::vec3( COLORBYTE( 187 ), COLORBYTE( 96 ), COLORBYTE( 4 ) );
	else if ( height <= 50 ) result = glm::vec3( COLORBYTE( 114 ), COLORBYTE( 191 ), COLORBYTE( 9 ) );
	else if ( height <= 60 ) result = glm::vec3( COLORBYTE( 113 ), COLORBYTE( 150 ), COLORBYTE( 10 ) );
	else if ( height <= 70 ) result = glm::vec3( COLORBYTE( 72 ), COLORBYTE( 140 ), COLORBYTE( 12 ) );
	else if ( height <= 80 ) result = glm::vec3( COLORBYTE( 23 ), COLORBYTE( 140 ), COLORBYTE( 11 ) );
	else if ( height <= 90 ) result = glm::vec3( COLORBYTE( 28 ), COLORBYTE( 123 ), COLORBYTE( 45 ) );
	else if ( height <= 100 ) result = glm::vec3( COLORBYTE( 188 ), COLORBYTE( 203 ), COLORBYTE( 194 ) );

	return result;
}