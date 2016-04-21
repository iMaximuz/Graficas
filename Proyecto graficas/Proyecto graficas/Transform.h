#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "MathLib.h"


struct Transform {

	glm::mat4 worldMatrix;

public:


	Transform() : worldMatrix( glm::mat4() ) {}
	Transform( glm::mat4 _worldMatrix ) : worldMatrix( _worldMatrix ) { }

	void Translate( glm::vec3 transVec );
	void Rotate( GLfloat rads, glm::vec3 rotVec );
	void Scale( glm::vec3 scaleVec );

	inline void LoadIdentity() { worldMatrix = glm::mat4(); }
	inline glm::mat4 GetWorldMatrix() { return worldMatrix; }
	
};

#endif