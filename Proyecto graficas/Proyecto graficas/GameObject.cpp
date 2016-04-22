#include "GameObject.h"


GameObject::~GameObject()
{
	for ( int i = 0; i < children.size(); i++ ) {
		delete children[i];
	}
	children.clear();
}

void GameObject::InputChildren(InputInfo input, GLfloat dt )
{

	for ( int i = 0; i < children.size(); i++ )
		children[i]->Input(input, dt );
	
	Input( input, dt );
}

void GameObject::UpdateChildren( GLfloat dt )
{
	for ( int i = 0; i < children.size(); i++ )
		children[i]->Update( dt );

	Update( dt );

}

void GameObject::RenderChildren( Shader shader, Camera* cam)
{
	for ( int i = 0; i < children.size(); i++ )
		children[i]->RenderChildren( shader, cam);

	Render( shader, cam);

}

void GameObject::AddChild( GameObject* child )
{
	this->children.push_back( child );
}
