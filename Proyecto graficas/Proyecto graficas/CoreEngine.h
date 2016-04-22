#ifndef _COREENGINE_H_
#define _COREENGINE_H_

#include "Precompiled.h"

class Window;
class Game;

enum {
	GLEW_Failed,
	CoreEngine_Failed,
	CoreEngine_Ok
};

class CoreEngine {

	Window* window;
	Game* game;

	int state;

public:

	CoreEngine( Game* _game, Window* _window );
	~CoreEngine();

	void Run();

	inline int GetCoreEngineState() { return state; }

};

#endif // !_COREENGINE_H_
