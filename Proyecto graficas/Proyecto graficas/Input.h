#pragma once
#include <glew.h>
#include <glfw3.h>

 
struct InputInfo {
	GLboolean keys[1024];
	GLboolean leftMouse;
	GLboolean rightMouse;
	GLdouble mousePosX;
	GLdouble mousePosY;
	GLdouble scrollAxis;
};

static InputInfo g_Input;

//void Key_Callback( GLFWwindow* window, int key, int scancode, int action, int mode );
//
//void Mouse_Callback( GLFWwindow* window, double xpos, double ypos );
//
//void Scroll_callback( GLFWwindow* window, double xoffset, double yoffset );