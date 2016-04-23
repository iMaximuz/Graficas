#pragma once

struct InputInfo {
	GLboolean keys[1024];
	GLboolean leftMouse;
	GLboolean rightMouse;
	GLdouble mousePosX;
	GLdouble mousePosY;
	GLdouble mouseDeltaX;
	GLdouble mouseDeltaY;
	GLdouble scrollAxis;

	inline void Reset() {
		mouseDeltaX = 0.0f;
		mouseDeltaY = 0.0f;
	}

};

static InputInfo g_Input;
