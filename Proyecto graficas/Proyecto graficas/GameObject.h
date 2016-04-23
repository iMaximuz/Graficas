#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_


//#include <memory>

#include "Precompiled.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Input.h"


class GameObject {

	std::vector<GameObject*> children;

public:
	
	~GameObject();

	Transform transform;

	void InputChildren(InputInfo input, GLfloat dt );
	void UpdateChildren( GLfloat dt );
	void RenderChildren( Shader shader );


	virtual void Input( InputInfo input, GLfloat dt ) { };
	virtual void Update( GLfloat dt ) { };
	virtual void Render( Shader shader ) { };

	void AddChild( GameObject* child );

};

#endif