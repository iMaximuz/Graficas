#include "Transform.h"


void Transform::Translate( glm::vec3 transVec ) {
	this->worldMatrix = glm::translate( this->worldMatrix, transVec );
}

void Transform::Rotate( GLfloat rads, glm::vec3 rotVec ) {
	this->worldMatrix = glm::rotate( this->worldMatrix, rads, rotVec );
}

void Transform::Scale( glm::vec3 scaleVec ) {
	this->worldMatrix = glm::scale( this->worldMatrix, scaleVec );
}