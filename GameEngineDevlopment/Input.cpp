#include "Input.h"
#include "MouseEventData.h"
#include "Publisher.h"
#include "Broker.h"

Input::Input()
{
    for (int i = 0; i < SDL_SCANCODE_COUNT; i++)
        lastFrameKeyState[i] = false;

}
void Input::UpdateKeyBoard()
{
   
    currentKeyStates = SDL_GetKeyboardState(NULL);

}

void Input::UpdateMouse(const SDL_Event& event)
{
    MouseEventData* mouseEventData = nullptr;

    switch (event.type) {

    case SDL_EVENT_MOUSE_MOTION:
        mousePositon = event.motion;
        mouseEventData =
            new MouseEventData(*this, mouseButton, mousePositon, mouseWheel);
        Publish("MousePositionUpdate", mouseEventData);
        break;

    case SDL_EVENT_MOUSE_WHEEL:
        mouseWheel = event.wheel;
        mouseEventData =
            new MouseEventData(*this, mouseButton, mousePositon, mouseWheel);
        Publish("MouseWheelUpdate", mouseEventData);
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        mouseButton = event.button;
        mouseEventData =
            new MouseEventData(*this, mouseButton, mousePositon, mouseWheel);
        Publish("MouseButtonUpdate", mouseEventData);
        break;

    default:
        break;
    }

    delete mouseEventData;
    mouseEventData = nullptr;
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
    if (lastFrameKeyState[scanCode] && currentKeyStates[scanCode])
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

Input& Input::INSTANCE()
{
    if (!Input::_instance)
        Input::_instance = new Input();

    return *Input::_instance;
}
Input* Input::_instance = nullptr;
