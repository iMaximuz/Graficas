#include "Planet.h"
#include "NoiseMap.h"
#include "Heightmap.h"
#include <SOIL\SOIL.h>

#define COLORBYTE(x) (GLfloat)x / 255.0f


Planet::Planet( GLfloat maxRad, GLfloat slices, GLfloat stacks, GLuint seed = 0, GLuint noiseSize = 16 ){
	this->maxRad = maxRad;
	this->slices = slices;
	this->stacks = stacks;

	renderMode = Mesh_Arrays;
	GeneratePlanet(seed, noiseSize);
}

Planet::Planet( const GLchar* filePath, GLfloat minRad, GLfloat maxRad ) {
	this->maxRad = maxRad;
	this->minRad = minRad;
	LoadHeightMap( filePath, minRad, maxRad );
}

void Planet::LoadHeightMap( const GLchar* filePath,  GLfloat minRad, GLfloat maxRad ) {

	HeightmapFile hMap;

	GLubyte *image;
	image = SOIL_load_image( filePath, &hMap.sizeX, &hMap.sizeY, 0, SOIL_LOAD_RGB );
	
	hMap.data = new GLfloat[hMap.sizeX * hMap.sizeY + 1];

	int stride = 0;
	for ( int y = 0; y < hMap.sizeY; y++ ) {
		for ( int x = 0; x < hMap.sizeX; x++ ) {
			hMap.data[y * hMap.sizeX + x] = COLORBYTE( image[(y * hMap.sizeX + x) * 3] );
			stride += 3;
		}
	}

	this->stacks = hMap.sizeX;
	this->slices = hMap.sizeY;
	GLint vertexCount = stacks - 2;
	
	GLfloat theta = 0;
	GLfloat phi = 0;

	for ( int z = 0; z < slices; z++ ) {
		for ( int x = 0; x < stacks; x++ ) {

			Vertex vert[3];

			GLfloat rad[3];
			rad[0] = myMath::MapValue( hMap.data[z * vertexCount + x], 0, 1, minRad, maxRad );
			rad[1] = myMath::MapValue( hMap.data[(z + 1) * vertexCount + x], 0, 1, minRad, maxRad );
			rad[2] = myMath::MapValue( hMap.data[z * vertexCount + (x + 1)], 0, 1, minRad, maxRad );
	
			theta = z * PI * 2 / slices;
			phi = x * PI / stacks;
			vert[0].position.x = rad[0] * cosf( theta )* sinf( phi );
			vert[0].position.y = rad[0] * cosf( phi );
			vert[0].position.z = rad[0] * sinf( theta )* sinf( phi );
			vert[0].texCoord.x = (1 / vertexCount)*x;
			vert[0].texCoord.y = (1 / vertexCount)*z;

			theta = (z + 1) * PI * 2 / slices;
			phi = x * PI / stacks;
			vert[1].position.x = rad[1] * cosf( theta )* sinf( phi );
			vert[1].position.y = rad[1] * cosf( phi );
			vert[1].position.z = rad[1] * sinf( theta )* sinf( phi );
			vert[1].texCoord.x = (1 / vertexCount)*x;
			vert[1].texCoord.y = (1 / vertexCount)*z;

			theta = z * PI * 2 / slices;
			phi = (x + 1) * PI / stacks;
			vert[2].position.x = rad[2] * cosf( theta )* sinf( phi );
			vert[2].position.y = rad[2] * cosf( phi );
			vert[2].position.z = rad[2] * sinf( theta )* sinf( phi );
			vert[2].texCoord.x = (1 / vertexCount)*x;
			vert[2].texCoord.y = (1 / vertexCount)*z;
			

			glm::vec3 v1 = vert[1].position - vert[0].position;
			glm::vec3 v2 = vert[1].position - vert[2].position;

			glm::vec3 normal = glm::cross( v2, v1 );

			vert[0].normal = normal;
			vert[1].normal = normal;
			vert[2].normal = normal;


#if FLAT_SHADING
			GLfloat averageRad = (rad[0] + rad[1] + rad[2]) / 3;
			GLfloat totalRad = myMath::MapValue( averageRad, minRad, maxRad, 0, 100 );;
			glm::vec3 finalColor = CalculateHeigthColor( totalRad );

			vert[0].color = finalColor;
			vert[1].color = finalColor;
			vert[2].color = finalColor;
#else
			vert[0].color = CalculateHeigthColor( myMath::MapValue( rad[0], minRad, maxRad, 0, 100 ) );
			vert[1].color = CalculateHeigthColor( myMath::MapValue( rad[1], minRad, maxRad, 0, 100 ) );
			vert[2].color = CalculateHeigthColor( myMath::MapValue( rad[2], minRad, maxRad, 0, 100 ) );

#endif		

			mesh.vertices.push_back( vert[0] );
			mesh.vertices.push_back( vert[1] );
			mesh.vertices.push_back( vert[2] );

			rad[0] = myMath::MapValue( hMap.data[z * vertexCount + (x + 1)], 0, 1, minRad, maxRad);
			rad[1] = myMath::MapValue( hMap.data[(z + 1) * vertexCount + x], 0, 1, minRad, maxRad );
			rad[2] = myMath::MapValue( hMap.data[(z + 1) * vertexCount + (x + 1)], 0, 1, minRad, maxRad );

			theta = z * PI * 2 / slices;
			phi = (x + 1) * PI / stacks;
			vert[0].position.x = rad[0] * cosf( theta )* sinf( phi );
			vert[0].position.y = rad[0] * cosf( phi );
			vert[0].position.z = rad[0] * sinf( theta )* sinf( phi );
			vert[0].texCoord.x = (1 / vertexCount)*x;
			vert[0].texCoord.y = (1 / vertexCount)*z;

			theta = (z + 1) * PI * 2 / slices;
			phi = x * PI / stacks;
			vert[1].position.x = rad[1] * cosf( theta )* sinf( phi );
			vert[1].position.y = rad[1] * cosf( phi );
			vert[1].position.z = rad[1] * sinf( theta )* sinf( phi );
			vert[1].texCoord.x = (1 / vertexCount)*x;
			vert[1].texCoord.y = (1 / vertexCount)*z;

			theta = (z + 1) * PI * 2 / slices;
			phi = (x + 1) * PI / stacks;
			vert[2].position.x = rad[2] * cosf( theta )* sinf( phi );
			vert[2].position.y = rad[2] * cosf( phi );
			vert[2].position.z = rad[2] * sinf( theta )* sinf( phi );
			vert[2].texCoord.x = (1 / vertexCount)*x;
			vert[2].texCoord.y = (1 / vertexCount)*z;

			v1 = vert[2].position - vert[0].position;
			v2 = vert[2].position - vert[1].position;

			normal = glm::cross( v1, v2 );

			vert[0].normal = normal;
			vert[1].normal = normal;
			vert[2].normal = normal;

#if FLAT_SHADING
			averageRad = (rad[0] + rad[1] + rad[2]) / 3;
			totalRad = myMath::MapValue( averageRad, minRad, maxRad, 0, 100 );;
			finalColor = CalculateHeigthColor( totalRad );

			vert[0].color = finalColor;
			vert[1].color = finalColor;
			vert[2].color = finalColor;
#else
			vert[0].color = CalculateHeigthColor( myMath::MapValue( rad[0], minRad, maxRad, 0, 100 ) );
			vert[1].color = CalculateHeigthColor( myMath::MapValue( rad[1], minRad, maxRad, 0, 100 ) );
			vert[2].color = CalculateHeigthColor( myMath::MapValue( rad[2], minRad, maxRad, 0, 100 ) );

#endif		

			mesh.vertices.push_back( vert[0] );
			mesh.vertices.push_back( vert[1] );
			mesh.vertices.push_back( vert[2] );

		}
	}

	delete hMap.data;
	SOIL_free_image_data( image );

	mesh.setupMesh( Mesh_Arrays );
}

void Planet::GeneratePlanet(GLuint seed, GLuint noiseSize) {
	GLint vertexCount = stacks + 1;

	NoiseMap noiseMap(seed, noiseSize, vertexCount, vertexCount);
	//TODO: Calcular normales por cara
	glm::vec3* normals = new glm::vec3[(slices + 1) * (stacks + 1) * 2];

	GLfloat nPoleAverage = 0;
	GLfloat sPoleAverage = 0;

	if (this->renderMode == Mesh_Elements) {

		for (int z = 0; z < slices + 1; z++) {
			for (int x = 0; x < stacks + 1; x++) {

				Vertex vert;

				GLfloat theta = z*PI * 2 / slices;
				GLfloat phi = x*PI / stacks;


				//TODO: Acomodar el orden correcto

				GLfloat rad = (noiseMap.noiseData[z * vertexCount + x] * maxRad);

				vert.position.x = rad * cosf(theta)* sinf(phi);
				vert.position.y = rad * cosf(phi);
				vert.position.z = rad * sinf(theta)* sinf(phi);
				vert.normal = glm::vec3(0.0f, 1.0f, 0.0f);
				vert.texCoord.x = (1 / vertexCount)*x;
				vert.texCoord.y = (1 / vertexCount)*z;

				mesh.vertices.push_back(vert);


				if (x == 0)
					nPoleAverage += vert.position.y;
				else if (x % (int)(stacks) == 0)
					sPoleAverage += vert.position.y;

			}
		}

		nPoleAverage /= vertexCount;
		sPoleAverage /= vertexCount;

		for (int z = 0; z < slices + 1; z++) {
			for (int x = 0; x < stacks + 1; x++) {
				if (x == 0)
					mesh.vertices[z * vertexCount + x].position.y = nPoleAverage;
				else if (x % (int)(stacks) == 0)
					mesh.vertices[z * vertexCount + x].position.y = sPoleAverage;

				if (z == 0) {
					glm::vec3 average = mesh.vertices[(z)* vertexCount + x].position + mesh.vertices[(z + slices) * vertexCount + x].position;
					average *= 0.5f;

					mesh.vertices[(z)* vertexCount + x].position = average;
					mesh.vertices[(z + slices) * vertexCount + x].position = average;
				}

			}
		}

		int index = 0;


		for (int z = 0; z < slices; z++) {
			for (int x = 0; x < stacks; x++) {


				GLuint start = z * vertexCount + x;
				glm::vec3 v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start].position);
				glm::vec3 v2 = (mesh.vertices[start + 1].position - mesh.vertices[start].position);
				//normals.push_back( glm::normalize( glm::cross( v1, v2 ) ) );
				normals[index++] = glm::normalize(glm::cross(v1, v2));

				v1 = (mesh.vertices[start + vertexCount].position - mesh.vertices[start + vertexCount + 1].position);
				v2 = (mesh.vertices[start + 1].position - mesh.vertices[start + vertexCount + 1].position);
				//normals.push_back( glm::normalize( glm::cross( v2, v1 ) ) );
				normals[index++] = glm::normalize(glm::cross(v2, v1));


				//mesh.vertices[vertexIndex].normal = normalAverage;

				mesh.indices.push_back(start);
				mesh.indices.push_back(start + vertexCount);
				mesh.indices.push_back(start + 1);

				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + vertexCount);
				mesh.indices.push_back(start + vertexCount + 1);


			}
		}

		for (GLuint z = 0; z < slices; z++)
		{
			for (GLuint x = 0; x < stacks; x++) {

				GLuint start = z * stacks + x;
				glm::vec3 normalAverage;
				normalAverage += normals[start + 1];
				normalAverage += normals[start + 2];
				normalAverage += normals[start + 3];
				normalAverage += normals[start + (int)stacks];
				normalAverage += normals[start + (int)stacks + 1];
				normalAverage += normals[start + (int)stacks + 2];

				glm::normalize(normalAverage);

				GLuint vertexIndex = (z + 1) * (vertexCount)+(x + 1);
				mesh.vertices[vertexIndex].normal = normalAverage;
			}
		}
	}
	else if (this->renderMode == Mesh_Arrays) {

		GLfloat theta = 0;
		GLfloat phi = 0;

		for (int z = 0; z < slices; z++) {
			for (int x = 0; x < stacks; x++) {

				Vertex vert[3];

				GLfloat rad = (noiseMap.noiseData[z * vertexCount + x] * maxRad);

				theta = z * PI * 2 / slices;
				phi = x * PI / stacks;
				vert[0].position.x = rad * cosf(theta)* sinf(phi);
				vert[0].position.y = rad * cosf(phi);
				vert[0].position.z = rad * sinf(theta)* sinf(phi);
				vert[0].texCoord.x = (1 / vertexCount)*x;
				vert[0].texCoord.y = (1 / vertexCount)*z;
				vert[0].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );


				rad = (noiseMap.noiseData[(z + 1) * vertexCount + x] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = x * PI / stacks;
				vert[1].position.x = rad * cosf(theta)* sinf(phi);
				vert[1].position.y = rad * cosf(phi);
				vert[1].position.z = rad * sinf(theta)* sinf(phi);
				vert[1].texCoord.x = (1 / vertexCount)*x;
				vert[1].texCoord.y = (1 / vertexCount)*z;
				vert[1].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );

				rad = (noiseMap.noiseData[z * vertexCount + (x + 1)] * maxRad);

				theta = z * PI * 2 / slices;
				phi = (x + 1) * PI / stacks;
				vert[2].position.x = rad * cosf(theta)* sinf(phi);
				vert[2].position.y = rad * cosf(phi);
				vert[2].position.z = rad * sinf(theta)* sinf(phi);
				vert[2].texCoord.x = (1 / vertexCount)*x;
				vert[2].texCoord.y = (1 / vertexCount)*z;
				vert[2].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );

				glm::vec3 v1 = vert[1].position - vert[0].position;
				glm::vec3 v2 = vert[1].position - vert[2].position;

				glm::vec3 normal = glm::cross(v2, v1);

				vert[0].normal = normal;
				vert[1].normal = normal;
				vert[2].normal = normal;
				
				mesh.vertices.push_back(vert[0]);
				mesh.vertices.push_back(vert[1]);
				mesh.vertices.push_back(vert[2]);

				rad = (noiseMap.noiseData[z * vertexCount + (x + 1)] * maxRad);

				theta = z * PI * 2 / slices;
				phi = (x + 1) * PI / stacks;
				vert[0].position.x = rad * cosf(theta)* sinf(phi);
				vert[0].position.y = rad * cosf(phi);
				vert[0].position.z = rad * sinf(theta)* sinf(phi);
				vert[0].texCoord.x = (1 / vertexCount)*x;
				vert[0].texCoord.y = (1 / vertexCount)*z;
				vert[0].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );

				rad = (noiseMap.noiseData[(z + 1) * vertexCount + x] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = x * PI / stacks;
				vert[1].position.x = rad * cosf(theta)* sinf(phi);
				vert[1].position.y = rad * cosf(phi);
				vert[1].position.z = rad * sinf(theta)* sinf(phi);
				vert[1].texCoord.x = (1 / vertexCount)*x;
				vert[1].texCoord.y = (1 / vertexCount)*z;
				vert[1].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );

				rad = (noiseMap.noiseData[(z + 1) * vertexCount + (x + 1)] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = (x + 1) * PI / stacks;
				vert[2].position.x = rad * cosf(theta)* sinf(phi);
				vert[2].position.y = rad * cosf(phi);
				vert[2].position.z = rad * sinf(theta)* sinf(phi);
				vert[2].texCoord.x = (1 / vertexCount)*x;
				vert[2].texCoord.y = (1 / vertexCount)*z;
				vert[2].color = CalculateHeigthColor( myMath::MapValue( rad, 0, maxRad, 0, 100 ) );

				v1 = vert[2].position - vert[0].position;
				v2 = vert[2].position - vert[1].position;

				normal = glm::cross(v1, v2);

				vert[0].normal = normal;
				vert[1].normal = normal;
				vert[2].normal = normal;

				mesh.vertices.push_back(vert[0]);
				mesh.vertices.push_back(vert[1]);
				mesh.vertices.push_back(vert[2]);

			}
		}

	}


	delete normals;

	mesh.setupMesh(this->renderMode);
}

void Planet::GenerateNewPlanet( GLfloat maxRad, GLfloat slices, GLfloat stacks, GLuint seed = 0, GLuint noiseSize = 16 ){
	this->slices = slices;
	this->maxRad = maxRad;
	this->stacks = stacks;
	this->renderMode = Mesh_Arrays;
	GeneratePlanet( seed, noiseSize );
}

void Planet::Render( Shader shader ){
	glUniformMatrix4fv( glGetUniformLocation( shader.program, "model" ), 1, GL_FALSE, glm::value_ptr( this->transform.GetWorldMatrix() ) );
	mesh.Draw( shader );
}

glm::vec3 Planet::CalculateHeigthColor( GLfloat height ) {

	glm::vec3 result;

	if ( height <= 10 ) result = glm::vec3( COLORBYTE( 0 ), COLORBYTE( 100 ), COLORBYTE( 200 ) );
	else if ( height <= 20 ) result = glm::vec3( COLORBYTE( 0 ), COLORBYTE( 120 ), COLORBYTE( 200 ) );
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

void Planet::Update( GLfloat dt ) {

	GLfloat angle = glm::radians( 0.5f ) * dt;

	transform.Rotate( angle, glm::vec3( 0.0f, 1.0f, 0.0f ) );

}	