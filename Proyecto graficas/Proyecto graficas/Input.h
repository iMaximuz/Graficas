#pragma once

struct InputInfo {
	GLboolean keys[1024];
	GLboolean leftMouse;
	GLboolean rightMouse;
	GLdouble mousePosX;
	GLdouble mousePosY;
	GLdouble scrollAxis;
};

static InputInfo g_Input;
