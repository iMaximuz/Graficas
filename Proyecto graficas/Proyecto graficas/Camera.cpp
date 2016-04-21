#include "Camera.h"


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt( this->Position, this->Front + this->Position, this->Up );
}

void Camera::UpdateVectors() {

	glm::vec3 front;

	front.x = cos( glm::radians( Pitch ) ) * cos( glm::radians( Yaw ) );
	front.y = sin( glm::radians( Pitch ) );
	front.z = cos( glm::radians( Pitch ) ) * sin( glm::radians( Yaw ) );
	this->Front = front;
	this->Right = glm::normalize( glm::cross( this->Front, this->WorldUp ) );
	this->Up = glm::normalize( glm::cross( this->Right, this->Front ) );
}

void Camera::Rotate( GLfloat xoffset, GLfloat yoffset, GLboolean maxedPitch ) {
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	if ( maxedPitch ) {
		if ( this->Pitch > 89.0f )
			Pitch = 89.0f;
		else if ( this->Pitch < -89.0f )
			Pitch = -89.0f;
	}

	this->UpdateVectors();
}

void Camera::Move( CameraMovement direction, GLfloat deltaTime ) {

	GLfloat	velocity = this->MovementSpeed * deltaTime;
	
	if ( Sprinting )
		velocity *= 2;

	if ( direction == FORWARD )
		this->Position += this->Front * velocity;
	if ( direction == BACKWARD )
		this->Position -= this->Front * velocity;
	if ( direction == LEFT )
		this->Position += this->Right * velocity;
	if ( direction == RIGHT )
		this->Position -= this->Right * velocity;
	if ( direction == UP )
		this->Position += this->Up * velocity;
	if ( direction == DOWN )
		this->Position -= this->Up * velocity;
}

void Camera::Zoom( GLfloat yoffset ) {

	if ( this->ZoomAmount >= 1.0f && this->ZoomAmount <= 45.0f ) 
		this->ZoomAmount -= yoffset;
	if ( this->ZoomAmount < 1.0f )
		this->ZoomAmount = 1.0f;
	if ( this->ZoomAmount > 45.0f )
		this->ZoomAmount = 45.0f;
}