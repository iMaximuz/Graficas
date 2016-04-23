#include "CoreEngine.h"
#include "Input.cpp"

CoreEngine::CoreEngine( Game * _game, Window * _window ) : game(_game), window(_window)
{
	glewExperimental = GL_TRUE;
	if ( glewInit() != GLEW_OK ) {
		std::cout << "Failed to Initialize GLEW: " << glewGetErrorString( glewInit() ) << std::endl;
		state = GLEW_Failed;
	}

	glfwSetKeyCallback( window->glfwWindow, Key_Callback );
	glfwSetScrollCallback( window->glfwWindow, Scroll_callback );
	glfwSetCursorPosCallback( window->glfwWindow, Mouse_Callback );

	//TODO: Implementar lectura de botones del mouse
	//glfwSetMouseButtonCallback( window->glfwWindow, )

	glViewport( 0, 0, 800, 600 );

	game->SetWindow( this->window );

}

CoreEngine::~CoreEngine()
{
	delete game;
	delete window;
}

void CoreEngine::Run()
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	if ( game ) {

		game->Init();

		while ( !glfwWindowShouldClose( window->glfwWindow ) ) {

			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();

			game->Input( g_Input, deltaTime );

			game->Update( deltaTime );
			
			game->Render();

			g_Input.Reset();

			glfwSwapBuffers( window->glfwWindow );
		}
	}
	else {
		state = CoreEngine_Failed;
	}
}


