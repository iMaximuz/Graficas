#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>
#include <memory>
#include "GameComponent.h"
#include "MathLib.h"
#include "Shader.h"
#include "Transform.h"
#include "Input.h"

class GameObject {

	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;


public:
	
	~GameObject();

	Transform transform;

	void Input(InputInfo input, GLfloat dt );
	void Update( GLfloat dt );
	void Render( );

	void AddChild( GameObject* child );
	void AddComponent( GameComponent* component );

};

#endif