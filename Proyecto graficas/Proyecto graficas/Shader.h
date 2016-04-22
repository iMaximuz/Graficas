#ifndef _SHADER_H_
#define _SHADER_H_

#include "Precompiled.h"

class Shader {

public:

	GLuint program;

	Shader(const char* vertexPath, const char* fragmentPath);

	~Shader() {}

	void Use() { glUseProgram( this->program ); }

	void SetUniformf( const GLchar* uniformName, int uniformSize, float* value );

};

#endif