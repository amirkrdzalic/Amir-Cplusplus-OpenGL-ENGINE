#include "InputManager.h"
#include "GameEngine.h"
#include <iostream>
KeyEvent keyEvent;


InputManager::InputManager()
{

}

InputManager::~InputManager()
{
}

void InputManager::processInput()
{
	SDL_Event evt;

	while (SDL_PollEvent(&evt))
	{

		switch (evt.type)
		{
			//Quit Button
		case SDL_QUIT:
			exit(0);
			SDL_Quit();
			break;
		case SDL_MOUSEMOTION:
			_mousePosition.x = evt.motion.x;
			_mousePosition.y = evt.motion.y;
			_mouseVelocity.x = evt.motion.xrel;
			_mouseVelocity.y = evt.motion.yrel;
			moving = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			_mousePosition.x = evt.motion.x;
			_mousePosition.y = evt.motion.y;
			_mouseDown = true;
			break;

		case SDL_MOUSEBUTTONUP:
			_mouseDown = false;

			//KEY DOWN

		case SDL_KEYDOWN:
			switch (evt.key.keysym.sym)
			{
			case SDLK_a:
				keyEvent = KeyEvent::A_KEYDOWN;
				break;
			case SDLK_d:
				keyEvent = KeyEvent::D_KEYDOWN;
				break;
			case SDLK_UP:
				keyEvent = KeyEvent::UP_KEYDOWN;
				break;
			case SDLK_DOWN:
				keyEvent = KeyEvent::DOWN_KEYDOWN;
				break;
			case SDLK_w:
				keyEvent = KeyEvent::W_KEYDOWN;
				break;
			case SDLK_s:
				keyEvent = KeyEvent::S_KEYDOWN;
				break;
			case SDLK_p:
				keyEvent = KeyEvent::P_KEYDOWN;
				break;
			case SDLK_ESCAPE:
				exit(0);
				SDL_Quit();
				break;
			default:
				break;
			}
			break;

			//KEY UP

		case SDL_KEYUP:
			switch (evt.key.keysym.sym)
			{
			case SDLK_a:
				keyEvent = KeyEvent::A_KEYUP;
				break;
			case SDLK_d:
				keyEvent = KeyEvent::D_KEYUP;
				break;
			case SDLK_UP:
				keyEvent = KeyEvent::UP_KEYUP;
				break;
			case SDLK_DOWN:
				keyEvent = KeyEvent::DOWN_KEYUP;
				break;
			case SDLK_w:
				keyEvent = KeyEvent::W_KEYUP;
				break;
			case SDLK_s:
				keyEvent = KeyEvent::S_KEYUP;
				break;
			case SDLK_p:
				keyEvent = KeyEvent::P_KEYUP;
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
	_keyEvent = keyEvent;
}


