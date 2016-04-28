#include "Mesh.h"

Mesh::Mesh() {

	this->vertices.reserve( 100 );
	this->indices.reserve( 600 );
	this->textures.reserve( 10 );

	this->VAO = 0;
	this->VBO = 0;
	this->EBO = 0;
}

Mesh::Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures )
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->VAO = 0;
	this->VBO = 0;
	this->EBO = 0;
}

Mesh::~Mesh() {
	if ( this->VAO != 0 && this->VBO != 0 && this->EBO != 0 ) {
		glDeleteVertexArrays( 1, &this->VAO );
		glDeleteBuffers( 1, &this->VBO );
		glDeleteBuffers( 1, &this->EBO );
	}
}

void Mesh::setupMesh(MeshRenderMode mode) {

	this->renderMode = mode;

	if ( this->VAO != 0 && this->VBO != 0 && this->EBO != 0 ) {
		glDeleteVertexArrays( 1, &this->VAO );
		glDeleteBuffers( 1, &this->VBO );
		glDeleteBuffers( 1, &this->EBO );
	}

	glGenVertexArrays( 1, &this->VAO );
	glGenBuffers( 1, &this->VBO );
	glGenBuffers( 1, &this->EBO );

	glBindVertexArray( this->VAO );
	glBindBuffer( GL_ARRAY_BUFFER, this->VBO );
	glBufferData( GL_ARRAY_BUFFER, this->vertices.size() * sizeof( Vertex ), &this->vertices[0], GL_STATIC_DRAW );
	
	if (this->renderMode == Mesh_Elements) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	glEnableVertexAttribArray( 3 );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, normal ) );
	glVertexAttribPointer ( 2, 3, GL_FLOAT, GL_FALSE, sizeof ( Vertex ), (GLvoid*)offsetof ( Vertex, color ) );
	glVertexAttribPointer( 3, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)offsetof( Vertex, texCoord ) );
	glBindVertexArray( 0 );
}

void Mesh::Draw( Shader shader ) {

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for ( GLuint i = 0; i < this->textures.size(); i++ )
	{
		glActiveTexture( GL_TEXTURE0 + i ); // Activate proper texture unit before binding
											// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].type;
		if ( name == "texture_diffuse" )
			ss << diffuseNr++; // Transfer GLuint to stream
		else if ( name == "texture_specular" )
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1f( glGetUniformLocation( shader.program, ("material." + name + number).c_str() ), i );
		glBindTexture( GL_TEXTURE_2D, this->textures[i].id );
	}
	glActiveTexture( GL_TEXTURE0 );

	glBindVertexArray( this->VAO );
	//glDrawArrays( GL_TRIANGLES, 0, vertices.size() );
	if (this->renderMode == Mesh_Elements) {
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	}
	else if(this->renderMode == Mesh_Arrays) {
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}
	glBindVertexArray( 0 );

	for ( GLuint i = 0; i < this->textures.size(); i++ )
	{
		glActiveTexture( GL_TEXTURE0 + i );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
}