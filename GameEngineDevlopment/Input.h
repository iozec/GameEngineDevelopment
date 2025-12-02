#pragma once
#include <SDL3/SDL_events.h>
class Input
{
	public:

	//void Update(SDL_Event& e);
	void Update();
	bool lastFrameKeyState[SDL_SCANCODE_COUNT];
	const bool* currentKeyStates;
	bool isKeyDown(SDL_Scancode scanCode);
	bool isKeyHeld(SDL_Scancode scanCode);
	bool isKeyUp(SDL_Scancode scanCode);
	//bool IsKeyPressed(SDL_Scancode scanCode);
	void LateUpdate();

	Input();

	static Input* _instance;
	static Input& const INSTANCE();


	

};

