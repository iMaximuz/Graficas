#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Precompiled.h"
#include "MathLib.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
	
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	
	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;

	glm::mat4 projection;
	void UpdateVectors();

public:

	GLboolean Sprinting;
	GLfloat ZoomAmount;

	glm::vec3 Position;


	// Constructor with vectors

	Camera( GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ) ) : WorldUp( glm::vec3( 0.0f, 1.0f, 0.0f ) ), Yaw( YAW ),
		Pitch( PITCH ), Front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), MovementSpeed( SPEED ), MouseSensitivity( SENSITIVTY ), ZoomAmount( ZOOM ) {

		this->Position = position;

		projection = glm::perspective( fov, aspect, near, far );

		this->UpdateVectors();
	}

	Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ), GLfloat yaw = YAW, 
		GLfloat pitch = PITCH ) : Front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), MovementSpeed( SPEED ), MouseSensitivity( SENSITIVTY ), ZoomAmount( ZOOM )
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->UpdateVectors();

		projection = glm::perspective( 90.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );

	}
	// Constructor with scalar values
	Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch ) : Front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), 
		MovementSpeed( SPEED ), MouseSensitivity( SENSITIVTY ), ZoomAmount( ZOOM )
	{
		this->Position = glm::vec3( posX, posY, posZ );
		this->WorldUp = glm::vec3( upX, upY, upZ );
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->UpdateVectors();

		projection = glm::perspective( 90.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );
	}

	glm::mat4 GetViewMatrix();
	inline glm::mat4 GetProjectionMatrix() {
		return projection;
	}

	void Rotate(GLfloat xoffset, GLfloat yoffset, GLboolean maxedPitch = true);

	void Move(CameraMovement direction, GLfloat deltaTime);

	void Zoom(GLfloat yoffset);
};

#endif
