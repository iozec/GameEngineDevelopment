#pragma once
#include <SDL3/SDL_events.h>
class Input
{

	//void Update(SDL_Event& e);
	void Update();
	const bool* lastFrameKeyState;
	const bool* currentKeyStates;
	bool isKeyDown(SDL_Scancode scanCode);
	bool isKeyHeld(SDL_Scancode scanCode);
	bool isKeyUp(SDL_Scancode scanCode);
	//bool IsKeyPressed(SDL_Scancode scanCode);
	void Update();




};

