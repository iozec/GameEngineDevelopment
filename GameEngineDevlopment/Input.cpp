#include "Input.h"

Input::Input()
{
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
        lastFrameKeyState[i] = false;

}
void Input::Update()
{
   
    currentKeyStates = SDL_GetKeyboardState(NULL);

}

bool Input::isKeyDown(SDL_Scancode scanCode)
{
    bool result = false;
    if (lastFrameKeyState[scanCode] < currentKeyStates[scanCode])
        result = true;

    return result;
}

bool Input::isKeyHeld(SDL_Scancode scanCode)
{
    bool result = false;
    if (lastFrameKeyState[scanCode] == currentKeyStates[scanCode])
        result = true;

    return result;
}

bool Input::isKeyUp(SDL_Scancode scanCode)
{
    bool result = false;
    if (lastFrameKeyState[scanCode] > currentKeyStates[scanCode])
        result = true;

    return result;


}

void Input::LateUpdate()
{
    for(int i =0; i< SDL_SCANCODE_COUNT; i++)
        lastFrameKeyState[i] = currentKeyStates[i];


}

Input& const Input::INSTANCE()
{
    if (!Input::_instance)
        Input::_instance = new Input();

    return *Input::_instance;
}
Input* Input::_instance = nullptr;
