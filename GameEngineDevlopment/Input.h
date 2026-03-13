#pragma once
#include <SDL3/SDL_events.h>
#include "Publisher.h"
class Input : public Publisher
{
	public:

	//void Update(SDL_Event& e);
	void UpdateKeyBoard();
	void UpdateMouse(const SDL_Event& event);
	bool lastFrameKeyState[SDL_SCANCODE_COUNT];
	const bool* currentKeyStates;
	bool isKeyDown(SDL_Scancode scanCode);
	bool isKeyHeld(SDL_Scancode scanCode);
	bool isKeyUp(SDL_Scancode scanCode);
	SDL_MouseButtonEvent mouseButton;
	SDL_MouseMotionEvent mousePositon;
	SDL_MouseWheelEvent mouseWheel;
	//bool IsKeyPressed(SDL_Scancode scanCode);
	void LateUpdate();

	Input();

	static Input* _instance;
	static Input& INSTANCE();


	

};

