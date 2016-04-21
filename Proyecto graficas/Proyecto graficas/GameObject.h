#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>
#include <memory>
#include "MathLib.h"
#include "Shader.h"
#include "Transform.h"
#include "Input.h"


class GameObject {

	std::vector<GameObject*> children;


public:
	
	~GameObject();

	Transform transform;

	void InputChildren(InputInfo input, GLfloat dt );
	void UpdateChildren( GLfloat dt );
	void RenderChildren( );


	virtual void Input( InputInfo input, GLfloat dt ) {};
	virtual void Update( GLfloat dt ) {};
	virtual void Render() {};

	void AddChild( GameObject* child );

};

#endif