#include "GameObject.h"

GameObject::~GameObject()
{
	for ( int i = 0; i < children.size(); i++ ) {
		delete children[i];
	}
	children.clear();

	for ( int i = 0; i < components.size(); i++ ) {
		delete components[i];
	}
	components.clear();
}

void GameObject::Input(InputInfo input, GLfloat dt )
{

	for ( int i = 0; i < children.size(); i++ )
		children[i]->Input(input, dt );

	for ( int i = 0; i < children.size(); i++ )
		components[i]->Input(input, dt );
}

void GameObject::Update( GLfloat dt )
{
	for ( int i = 0; i < children.size(); i++ )
		children[i]->Update( dt );

	for ( int i = 0; i < children.size(); i++ )
		components[i]->Update( dt );
}

void GameObject::Render( )
{
	for ( int i = 0; i < children.size(); i++ )
		children[i]->Render( );

	for ( int i = 0; i < children.size(); i++ )
		components[i]->Render( );
}

void GameObject::AddChild( GameObject* child )
{
	this->children.push_back( child );
}

void GameObject::AddComponent( GameComponent* component )
{
	component->SetParent( this );
	this->components.push_back( component );
}