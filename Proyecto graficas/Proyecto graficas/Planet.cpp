#include "Planet.h"
#include "NoiseMap.h"

Planet::Planet( GLfloat maxRad, GLfloat slices, GLfloat stacks, GLuint seed = 0, GLuint noiseSize = 16 ){
	this->maxRad = maxRad;
	this->slices = slices;
	this->stacks = stacks;

	renderMode = Mesh_Arrays;
	GeneratePlanet(seed, noiseSize);
}



void Planet::GeneratePlanet(GLuint seed, GLuint noiseSize) {
	GLint vertexCount = stacks + 1;

	NoiseMap noiseMap(seed, noiseSize, vertexCount, vertexCount);
	//TODO: Calcular normales por cara
	glm::vec3* normals = new glm::vec3[(slices + 1) * (stacks + 1) * 2];

	GLfloat nPoleAverage = 0;
	GLfloat sPoleAverage = 0;

	if (this->renderMode == Mesh_Element) {

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

				rad = (noiseMap.noiseData[(z + 1) * vertexCount + x] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = x * PI / stacks;
				vert[1].position.x = rad * cosf(theta)* sinf(phi);
				vert[1].position.y = rad * cosf(phi);
				vert[1].position.z = rad * sinf(theta)* sinf(phi);
				vert[1].texCoord.x = (1 / vertexCount)*x;
				vert[1].texCoord.y = (1 / vertexCount)*z;

				rad = (noiseMap.noiseData[z * vertexCount + (x + 1)] * maxRad);

				theta = z * PI * 2 / slices;
				phi = (x + 1) * PI / stacks;
				vert[2].position.x = rad * cosf(theta)* sinf(phi);
				vert[2].position.y = rad * cosf(phi);
				vert[2].position.z = rad * sinf(theta)* sinf(phi);
				vert[2].texCoord.x = (1 / vertexCount)*x;
				vert[2].texCoord.y = (1 / vertexCount)*z;

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

				rad = (noiseMap.noiseData[(z + 1) * vertexCount + x] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = x * PI / stacks;
				vert[1].position.x = rad * cosf(theta)* sinf(phi);
				vert[1].position.y = rad * cosf(phi);
				vert[1].position.z = rad * sinf(theta)* sinf(phi);
				vert[1].texCoord.x = (1 / vertexCount)*x;
				vert[1].texCoord.y = (1 / vertexCount)*z;

				rad = (noiseMap.noiseData[(z + 1) * vertexCount + (x + 1)] * maxRad);

				theta = (z + 1) * PI * 2 / slices;
				phi = (x + 1) * PI / stacks;
				vert[2].position.x = rad * cosf(theta)* sinf(phi);
				vert[2].position.y = rad * cosf(phi);
				vert[2].position.z = rad * sinf(theta)* sinf(phi);
				vert[2].texCoord.x = (1 / vertexCount)*x;
				vert[2].texCoord.y = (1 / vertexCount)*z;

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
	this->maxRad = maxRad;
	this->slices = slices;
	this->stacks = stacks;
	this->renderMode = Mesh_Arrays;
	GeneratePlanet( seed, noiseSize );
}

void Planet::Render( Shader shader ){
	glUniformMatrix4fv( glGetUniformLocation( shader.program, "model" ), 1, GL_FALSE, glm::value_ptr( this->transform.GetWorldMatrix() ) );
	mesh.Draw( shader );
}
