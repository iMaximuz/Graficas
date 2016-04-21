#include<iostream>
#include <string>

//#include <glfw3.h>
#include "CoreEngine.h"
#include "SpaceGame.h"

//#include "Shader.h"
#include <SOIL\SOIL.h>
//#include "MathLib.h"
#include "Camera.h"
//#include "Heightmap.h"
//#include "GameObject.h"
//#include "Geometry.h"
//#include "Model.h"
//#include "Window.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600


//TODO LIST:
/*
	- Terminar el engine




*/



bool keys[1024];
Camera mainCamera(glm::vec3(0.0f, 1, 5.0f));
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat lightPosY;


void DoCameraMovement(Camera* camToMove, GLfloat deltaTime ) {

	if ( keys[GLFW_KEY_W] )
		camToMove->Move( FORWARD, deltaTime );
	if ( keys[GLFW_KEY_S] )
		camToMove->Move( BACKWARD, deltaTime );
	if ( keys[GLFW_KEY_A] )
		camToMove->Move( RIGHT, deltaTime );
	if ( keys[GLFW_KEY_D] )
		camToMove->Move( LEFT, deltaTime );
	if ( keys[GLFW_KEY_SPACE] )
		camToMove->Move( UP, deltaTime );
	if ( keys[GLFW_KEY_LEFT_CONTROL] )
		camToMove->Move( DOWN, deltaTime );
	if ( keys[GLFW_KEY_LEFT_SHIFT] )
		camToMove->Sprinting = true;
	else
		camToMove->Sprinting = false;
}

GLuint LoadTexture( const char* texturePath ) {

	GLuint result;
	glGenTextures( 1, &result );
	int width, height;
	unsigned char* image = SOIL_load_image( texturePath, &width, &height, 0, SOIL_LOAD_RGB );
	glBindTexture( GL_TEXTURE_2D, result );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	glGenerateMipmap( GL_TEXTURE_2D );
	SOIL_free_image_data( image );
	glBindTexture( GL_TEXTURE_2D, 0 );

	return result;
}


int main() {

	Window* window = new Window( 800, 600, "Graficas Computacionales" );
	window->LockMouse( true );
	
	Game* game = new SpaceGame();

	CoreEngine coreEngine( game, window );

	coreEngine.Run();


	//Shader basicShader( "Shaders//basic.vs", "Shaders//basic.fs" );

	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	//glEnable( GL_DEPTH_TEST );


	//Model testModel( "Models//Arwing_001.obj" );

	//Shader terrainShader( "Shaders//terrain.vert", "Shaders//terrain.frag" );
	////Heightmap hMap( 5, 5, 10 );
	//GLfloat heigthMapSize = 64.0f;
	//GameObject* hMap = new Heightmap(0, 12, 64, 64, 10 );
	//GameObject* sphere = new Sphere( 10.0f, 8, 8 );

	//GLfloat deltaTime = 0.0f;
	//GLfloat lastFrame = 0.0f;
	//while ( !glfwWindowShouldClose( window.glfwWindow ) ) {

	//	GLfloat currentFrame = glfwGetTime();
	//	deltaTime = currentFrame - lastFrame;
	//	lastFrame = currentFrame;

	//	glfwPollEvents();
	//	DoCameraMovement( &mainCamera, deltaTime );

	//	glm::mat4 model;
	//	glm::mat4 view;
	//	glm::mat4 projection;
	//	projection = glm::perspective( glm::radians(mainCamera.ZoomAmount), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );

	//	view = mainCamera.GetViewMatrix();

	//	hMap->localSpace = glm::mat4();
	//	hMap->localSpace = glm::translate( hMap->localSpace, glm::vec3( -(heigthMapSize * 0.5), 0.0f, -(heigthMapSize * 0.5) ) );
	//	//hMap->localSpace = glm::scale(hMap->localSpace,glm::vec3(64.0f, 10.0f, 64.0f));
	//	//hMap->localSpace = glm::translate( hMap->localSpace, glm::vec3( -(heigthMapSize * 0.5), 0.0f, -(heigthMapSize * 0.5)) );
	//	
	//	//if ( mainCamera.Position.y > 20.0f ) {
	//	//	mainCamera.Position.y = 15.0f;
	//	//	((Heightmap*)hMap)->GenerateNewTerrain(0, 8, 256, heigthMapSize, 10.0f );
	//	//}

	//	glClearColor( 0.05f, 0.05f, 0.05f, 1.0f );
	//	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//	//glm::vec3 lightPosition = glm::vec3( 0, 10.0f, 0 );
	//	glm::vec3 lightPosition = glm::vec3( std::sin( PI/16 * glfwGetTime() * 2) * 32.0f, 15.0f, std::cos( PI / 16 * glfwGetTime() * 2 ) * 32.0f );
	//	glm::vec3 lightColor = glm::vec3( 1.0f, 1.0f, 1.0f );
	//	glm::vec3 objectColor = glm::vec3( 0.7f, 0.5f, 0.2f );

	//	terrainShader.Use();
	//	glUniformMatrix4fv( glGetUniformLocation( terrainShader.program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
	//	glUniformMatrix4fv( glGetUniformLocation( terrainShader.program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
	//	glUniformMatrix4fv( glGetUniformLocation( terrainShader.program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
	//	glUniform3f( glGetUniformLocation( terrainShader.program, "viewPosition" ), mainCamera.Position.x, mainCamera.Position.y, mainCamera.Position.z );
	//	glUniform3f( glGetUniformLocation( terrainShader.program, "lightPosition" ), lightPosition.x, lightPosition.y, lightPosition.z );
	//	glUniform3f( glGetUniformLocation( terrainShader.program, "lightColor" ), lightColor.r, lightColor.g, lightColor.b );
	//	glUniform3f( glGetUniformLocation( terrainShader.program, "objectColor" ), objectColor.r, objectColor.g, objectColor.b );
	//	
	//	
	//	hMap->Render( terrainShader );

	//	//sphere->Draw( terrainShader );

	//	model = glm::translate( model, glm::vec3( 0.0, 15.0f, 0.0 ) );
	//	objectColor = glm::vec3( 0.2f, 0.3f, 0.7f );
	//	glUniformMatrix4fv( glGetUniformLocation( terrainShader.program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
	//	glUniform3f( glGetUniformLocation( terrainShader.program, "objectColor" ), objectColor.r, objectColor.g, objectColor.b );

	//	testModel.Draw( terrainShader );

	//	glfwSwapBuffers( window.glfwWindow );
	//}
	//glfwTerminate();
	return 0;
}



