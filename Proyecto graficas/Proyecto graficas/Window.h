#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Precompiled.h"

enum {
	Window_Success,
	Window_Failed,
};

class Window{

	int state;

public:
	
	int width;
	int height;
	GLFWwindow* glfwWindow;

	Window(int _width, int _height, const char* Title);
	~Window();

	inline int GetWindowState() { return state; }
	inline void LockMouse(bool lockMouse){ 
		lockMouse ? glfwSetInputMode( glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED ) : glfwSetInputMode( glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}
};


#endif // !_WINDOW_H_
