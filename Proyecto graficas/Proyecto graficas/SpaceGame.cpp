#include "SpaceGame.h"

#include "Heightmap.h"
#include "Geometry.h"
#include "Planet.h"
//#include "Model.h"


/*
TODO LIST

	- Crear la clase SphereData que me permita solo obtener los valores de los vertices individuales para despues crear el mesh por separado
	- Mejorar la generacion de "planetas" usando la clase SphereData
	- Renombrar la clase planetas
	- Mejorar la paleta de colores del planeta
	- Cargar el modelo de la nave
	- Crear skydome
	- Crear el Sol con un mesh animado como si fuera agua
	- Manejar la nave en primera persona
	- Manejar la nave en tercera persona
	- Disparar
	- "Colisionar" con asteroides
	- Crear enemigos
	
*/





#define MAX_PLANETS			5

Shader* basicShader;
Planet *planets;
Sphere *sphere;
Sphere *Skydome;
Heightmap *terreno;


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

	terreno = new Heightmap(0, 16, 32, 100, 50);
	sphere = new Sphere( 2, 32, 32, Mesh_Arrays );
	Sphere* esfera = new Sphere(2, 32, 32, Mesh_Arrays);
	

	//Model* nave = new Model( "Models/Arwing_001.obj" );

	//Planet *planet = new Planet( 700, 128, 128, 0, 512 );
	Planet *planet = new Planet( "Textures//moon3.bmp", 980, 1000 );
	planet->transform.Translate( glm::vec3( 0, 0, -1300));
	
	planets = new Planet[MAX_PLANETS];
	
	glm::vec3 maxDistance = glm::vec3( 200, 200, -200 );



	for ( int i = 0; i < MAX_PLANETS; i++ ) {

		GLfloat randX = rand() % (int)maxDistance.x - 100;
		GLfloat randY = rand() % (int)maxDistance.y - 100;
		GLfloat randZ = rand() % (int)maxDistance.z - 100;
		
		GLfloat randRad = rand() % 9 + 1;

		planets[i].GenerateNewPlanet( 9, 10, 16, 16, rand(),  16);
		planets[i].transform.Translate( glm::vec3( randX, randY, randZ ) );

	}

	terreno->transform.Translate(glm::vec3(-terreno->GetWorldSize() * 0.5f , 0.0f, -terreno->GetWorldSize() * 0.5f));


	AddObject( esfera );
	AddObject( sphere );
	AddObject( planet );
	//AddObject( nave );
	AddObject( terreno );
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

	if (input.keys[GLFW_KEY_BACKSPACE]) {
		terreno->GenerateNewTerrain ( rand (), 32, 32, 100, 100 );
		terreno->transform.worldMatrix = glm::mat4 ();
		terreno->transform.Translate( glm::vec3( -terreno->GetWorldSize() * 0.5f, -50.0f, -terreno->GetWorldSize() * 0.5f ) );
	}

	if ( input.keys[GLFW_KEY_ESCAPE] ) {
		this->LockMouse( false );
	}

	RootInput( input, dt );
}

void SpaceGame::Update( GLfloat dt ){


	for ( int i = 0; i < MAX_PLANETS; i++ ) {


		planets[i].transform.Rotate( dt / (rand() % 4 + 1), glm::vec3( 1.0f, 1.0f, 1.0f ) );

	}


	RootUpdate( dt );
}

void SpaceGame::Render(){

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glm::vec3 lightPosition = glm::vec3( 10.0f, 0.0f, 0 );
	glm::vec3 lightPosition = glm::vec3( std::sin( PI/16 * glfwGetTime() * 2) * 32.0f, 15.0f, std::cos( PI / 16 * glfwGetTime() * 2 ) * 32.0f );
	sphere->transform.worldMatrix = glm::mat4();
	sphere->transform.Translate( lightPosition );

	glm::vec3 lightColor = glm::vec3( 1.0f, 1.0f, 1.0f );
	glm::vec3 objectColor = glm::vec3( 0.6f, 0.6f, 0.6f );

	#if 0
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	#else
	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
	#endif
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
