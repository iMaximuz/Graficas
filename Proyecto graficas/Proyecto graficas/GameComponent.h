#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_

#include "Shader.h"
#include "Transform.h"
#include "Input.h"

class GameObject;

class GameComponent
{
public:

	void SetParent( GameObject* parent );


	virtual void Input( InputInfo input, GLfloat dt ) = 0;
	virtual void Update( GLfloat dt ) = 0;
	virtual void Render( ) = 0;

	Transform* GetTransform();

private:

	GameObject* parent;

};

#endif // !_GAMECOMPONENT_H_
