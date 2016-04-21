#ifndef _COREENGINE_H_
#define _COREENGINE_H_

#define GLEW_STATIC
#include <glew.h>
#include "Window.h"
#include "Game.h"
#include "Input.cpp"

enum {
	GLEW_Failed,
	CoreEngine_Failed,
	CoreEngine_Ok
};

class CoreEngine {


	Window* window;
	Game* game;
	RenderEngine* renderEngine;

	int state;

public:

	CoreEngine( Game* _game, Window* _window );
	~CoreEngine();

	void Run();

	inline int GetCoreEngineState() { return state; }

};

#endif // !_COREENGINE_H_
