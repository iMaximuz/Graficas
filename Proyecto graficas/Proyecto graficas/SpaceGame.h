#ifndef _SPACEGAME_H_
#define _SPACEGAME_H_

#include "Game.h"

class SpaceGame : public Game{

	Camera mainCamera;



public:
	SpaceGame ();
	~SpaceGame ();

	
	void Init();
	void Input( InputInfo input, GLfloat dt );
	void Update( GLfloat dt );
	void Render();

};



#endif // !_SPACEGAME_H_
