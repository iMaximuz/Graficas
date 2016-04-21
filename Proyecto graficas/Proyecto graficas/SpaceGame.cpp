#include "SpaceGame.h"

SpaceGame::SpaceGame(){

}

SpaceGame::~SpaceGame(){

}

void SpaceGame::Init(){
	



}

void SpaceGame::Input( InputInfo input, GLfloat dt){

	

	if ( input.keys[GLFW_KEY_ESCAPE] ) {
		this->LockMouse( false );
	}

	RootInput( g_Input, dt );
}

void SpaceGame::Update( GLfloat dt ){


	RootUpdate( dt );

}

void SpaceGame::Render(){
	

	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	RootRender( );

}
