#include "Input.h"

Input::Input()
{
    lastFrameKeyState = SDL_GetKeyboardState(NULL);

}
void Input::Update()
{
   
    currentKeyStates = SDL_GetKeyboardState(NULL);

}

bool Input::isKeyDown(SDL_Scancode scanCode)
{
    return false;
}

bool Input::isKeyHeld(SDL_Scancode scanCode)
{
    return false;
}

bool Input::isKeyUp(SDL_Scancode scanCode)
{
    return false;
}
