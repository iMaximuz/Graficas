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


}

void SpaceGame::Update( GLfloat dt ){



}

void SpaceGame::Render(){

	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	

}
