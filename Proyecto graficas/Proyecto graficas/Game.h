#ifndef _GAME_H_
#define _GAME_H_

#include <glew.h>
#include "Window.h"
#include "GameObject.h"
#include "Input.h"

class Game {

	GameObject root;
	Window* window;

public:

	virtual void Init() = 0;
	inline void RootInput( InputInfo input, GLfloat dt ) { root.Input(input, dt ); }
	inline void RootUpdate( GLfloat dt ) { root.Update( dt ); }
	inline void RootRender() { root.Render(); }
	virtual void Input( InputInfo input, GLfloat dt) = 0;
	virtual void Update(GLfloat dt) = 0;
	virtual void Render() = 0;

	inline void AddObject( GameObject* newObject ) {
		root.AddChild( newObject );
	}

	inline GameObject* GetRootObject() { return &root; }

	inline void SetWindow( Window* newWindow ) { window = newWindow; }
	inline void CloseWindow() { glfwSetWindowShouldClose( window->glfwWindow, GL_TRUE ); }
	inline void LockMouse( bool lock ) { window->LockMouse( lock ); }
};

#endif
