#include "SpaceGame.h"

#include "Heightmap.h"
#include "Geometry.h"
#include "Planet.h"

#define MAX_PLANETS			5

Shader* basicShader;
Planet *planets;

SpaceGame::SpaceGame() {


}


SpaceGame::~SpaceGame(){
	delete basicShader;
	delete planets;

}

void SpaceGame::Init(){
	

	glEnable( GL_DEPTH_TEST );

	this->mainCamera = new Camera( glm::radians( 90.0f ), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f );


	basicShader = new Shader( "Shaders/terrain.vert", "Shaders/terrain.frag" );

	Heightmap *terreno = new Heightmap(0, 16, 32, 100, 50);
	Sphere *sphere = new Sphere( 10, 32, 32 );

	//GameObject* planets = new GameObject();
	//Planet *planet = new Planet( 10, 32, 32, 0, 128 );
	//Planet *planet2 = new Planet( 10, 32, 32, 0, 128 );
	//planets->AddChild( (GameObject*)planet );
	//planets->AddChild( (GameObject*)planet2 );

	planets = new Planet[MAX_PLANETS];
	
	for ( int i = 0; i < MAX_PLANETS; i++ ) {

		GLfloat randX = rand() % 500 - 250;
		GLfloat randY = rand() % 200 - 100;
		GLfloat randZ = rand() % 500 - 250;
		
		GLfloat randRad = rand() % 70 + 50;

		planets[i].GenerateNewPlanet( randRad, 32, 32, rand(), 32 );
		planets[i].transform.Translate( glm::vec3( randX, randY, randZ ) );

	}

	terreno->transform.Translate(glm::vec3(-terreno->GetWorldSize().x * 0.5f, 0.0f, -terreno->GetWorldSize().y * 0.5f));

	//AddObject( sphere );
	//AddObject( (GameObject*)planet );
	//AddObject( terreno );
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

	RootInput( input, dt );
}

void SpaceGame::Update( GLfloat dt ){

	RootUpdate( dt );
}

void SpaceGame::Render(){

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glm::vec3 lightPosition = glm::vec3( 0, 10.0f, 0 );
	//glm::vec3 lightPosition = glm::vec3( std::sin( PI/16 * glfwGetTime() * 2) * 32.0f, 15.0f, std::cos( PI / 16 * glfwGetTime() * 2 ) * 32.0f );
	glm::vec3 lightColor = glm::vec3( 1.0f, 1.0f, 1.0f );
	glm::vec3 objectColor = glm::vec3( 0.6f, 0.6f, 0.6f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	basicShader->Use();

	glUniformMatrix4fv( glGetUniformLocation( basicShader->program, "projection" ), 1, GL_FALSE, glm::value_ptr( mainCamera->GetProjectionMatrix() ) );
	glUniformMatrix4fv( glGetUniformLocation( basicShader->program, "view" ), 1, GL_FALSE, glm::value_ptr( mainCamera->GetViewMatrix() ) );

	glUniform3f( glGetUniformLocation( basicShader->program, "viewPosition" ), mainCamera->Position.x, mainCamera->Position.y, mainCamera->Position.z );
	glUniform3f( glGetUniformLocation( basicShader->program, "lightPosition" ), lightPosition.x, lightPosition.y, lightPosition.z );
	glUniform3f( glGetUniformLocation( basicShader->program, "lightColor" ), lightColor.r, lightColor.g, lightColor.b );
	glUniform3f( glGetUniformLocation( basicShader->program, "objectColor" ), objectColor.r, objectColor.g, objectColor.b );

	for ( int i = 0; i < MAX_PLANETS; i++ ) {

		planets[i].Render( *basicShader );

	}

	RootRender( *basicShader );
}
