#include "SpaceGame.h"

#include "Heightmap.h"

Shader* basicShader;

SpaceGame::SpaceGame() {


}


SpaceGame::~SpaceGame(){

}

void SpaceGame::Init(){
	
	this->mainCamera = new Camera( glm::radians( 90.0f ), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );

	basicShader = new Shader( "Shaders/basic.vs", "Shaders/basic.fs" );

	Heightmap *Planeta = new Heightmap(0, 16, 32, 100, 50);
	
	Planeta->transform.Translate(glm::vec3(- Planeta->GetWorldSize().x * 0.5f, 0.0f, -Planeta->GetWorldSize().y * 0.5f));
	AddObject(Planeta);
}

void SpaceGame::Input( InputInfo input, GLfloat dt){


	if ( input.keys[GLFW_KEY_W] )
		mainCamera->Move( FORWARD, dt );
	if ( input.keys[GLFW_KEY_S] )
		mainCamera->Move( BACKWARD, dt );
	if ( input.keys[GLFW_KEY_A] )
		mainCamera->Move( RIGHT, dt );
	if ( input.keys[GLFW_KEY_D] )
		mainCamera->Move( LEFT, dt );
	if ( input.keys[GLFW_KEY_SPACE] )
		mainCamera->Move( UP, dt );
	if ( input.keys[GLFW_KEY_LEFT_CONTROL] )
		mainCamera->Move( DOWN, dt );
	if ( input.keys[GLFW_KEY_LEFT_SHIFT] )
		mainCamera->Sprinting = true;
	else
		mainCamera->Sprinting = false;

	mainCamera->Rotate( input.mouseDeltaX, input.mouseDeltaY );


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

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	basicShader->Use();
	RootRender( *basicShader );
}
