#include "Window.h"

Window::Window( int _width, int _height, const char * title ) : width(_width), height(_height){

	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	this->glfwWindow = glfwCreateWindow( _width, _height, title, nullptr, nullptr );
	if ( !this->glfwWindow ) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		state = Window_Failed;
	}
	else {
		state = Window_Success;
	}
	glfwMakeContextCurrent( this->glfwWindow );
}

Window::~Window()
{
	glfwTerminate();
}
