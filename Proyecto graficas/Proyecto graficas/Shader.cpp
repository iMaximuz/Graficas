#pragma once
#include "Shader.h"

Shader::Shader( const char* vertexPath, const char* fragmentPath ) {

	GLuint vertexShader, fragmentShader;
	std::string vertexBuffer, fragmentBuffer;
	const GLchar* vertexCode; 
	const GLchar* fragmentCode;

	FILE *pFile;

	pFile = fopen( vertexPath, "r" );
	if ( pFile ) {
		char ch;
		while ( (ch = fgetc( pFile )) != EOF ) {
			vertexBuffer += ch;
		}
		fclose( pFile );
	}
	else {
		std::cout << "ERROR_SHADER_VERTEX: File not found" << std::endl;
	}
	pFile = fopen( fragmentPath, "r" );
	if ( pFile ) {
		char ch;
		while ( (ch = fgetc( pFile )) != EOF ) {
			fragmentBuffer += ch;
		}
		fclose( pFile );
	}
	else {
		std::cout << "ERROR_SHADER_FRAGMENT: File not found" << std::endl;
	}

	vertexCode = vertexBuffer.c_str();
	fragmentCode = fragmentBuffer.c_str();

	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	glShaderSource( vertexShader, 1, &vertexCode, NULL );
	glShaderSource( fragmentShader, 1, &fragmentCode, NULL );
	glCompileShader( vertexShader );
	glCompileShader( fragmentShader );

	GLint success;
	GLchar infoLog[2048];

	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
		std::cout << "ERROR_SHADER_VERTEX: Compilation failed.\n" << infoLog << std::endl;
	}
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
		std::cout << "ERROR_SHADER_FRAGMENT: Compilation failed.\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );
	glLinkProgram( program );
	glGetProgramiv( program, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( program, 512, NULL, infoLog );
		std::cout << "ERROR_SHADER_PROGRAM: Linking failed.\n" << infoLog << std::endl;
	}

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

}

void Shader::SetUniformf(const GLchar* uniformName, int uniformSize, float* value) {

	GLint uniformLocation = glGetUniformLocation( this->program, uniformName );
	if ( uniformLocation < 0 ) {
		std::cout << "WARNING_SHADER: Uniform \"" << uniformName << "\" not found." << std::endl;
	}
	else {
		switch ( uniformSize )
		{
		case 1:
			glUniform1f( uniformLocation, *value);
			break;
		case 2:
			glUniform2f( uniformLocation, value[0], value[1] );
			break;
		case 3:
			glUniform3f( uniformLocation, value[0], value[1], value[2] );
			break;
		case 4:
			glUniform4f( uniformLocation, value[0], value[1], value[2], value[3] );
			break;
		default:
			std::cout << "WARNING_SHADER: Uniform size not acepted" << std::endl;
			break;
		}
		
	}

}
