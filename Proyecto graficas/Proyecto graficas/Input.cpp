#pragma once
#include "Input.h"
//#include <glew.h>
//#include <glfw3.h>

//static struct Input {
//	GLboolean keys[1024];
//	GLboolean leftMouse;
//	GLboolean rightMouse;
//	GLdouble mousePosX;
//	GLdouble mousePosY;
//	GLdouble scrollAxis;
//} input;



inline void Key_Callback( GLFWwindow* window, int key, int scancode, int action, int mode ) {

	if ( action == GLFW_PRESS )
		g_Input.keys[key] = true;
	else if ( action == GLFW_RELEASE )
		g_Input.keys[key] = false;
}

inline void Mouse_Callback( GLFWwindow* window, double xpos, double ypos ) {


	g_Input.mousePosX = xpos;
	g_Input.mousePosY = ypos;
	//if ( firstMouse )
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//GLfloat xoffset = xpos - lastX;
	//GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	//lastX = xpos;
	//lastY = ypos;

	//mainCamera.Rotate( xoffset, yoffset );
}

inline void Scroll_callback( GLFWwindow* window, double xoffset, double yoffset )
{
	g_Input.scrollAxis = yoffset;
	//mainCamera.Zoom( yoffset );
}