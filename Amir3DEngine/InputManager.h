#pragma once
#include "GLM\glm.hpp"

enum KeyEvent
{
	A_KEYDOWN = 1,
	A_KEYUP,
	D_KEYDOWN,
	D_KEYUP,
	UP_KEYDOWN,
	UP_KEYUP,
	DOWN_KEYDOWN,
	DOWN_KEYUP,
	W_KEYDOWN,
	W_KEYUP,
	S_KEYDOWN,
	S_KEYUP,
	P_KEYDOWN,
	P_KEYUP
};
class InputManager
{
public:
	InputManager();
	~InputManager();

	bool moving = false;

	void processInput();

	glm::vec2 getMousePosition()
	{
		return _mousePosition;
	}

	glm::vec2 getMouseVelocity()
	{
		return _mouseVelocity;
	}

	bool getMouseDown()
	{
		return _mouseDown;
	}

	KeyEvent getKeyEvent()
	{
		return _keyEvent;
	}

private:
	glm::vec2 _mousePosition;
	glm::vec2 _mouseVelocity;
	KeyEvent _keyEvent;
	bool _mouseDown;


};

