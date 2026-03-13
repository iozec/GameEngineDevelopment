#pragma once
#include "IEventData.h"
#include "SDL3/SDL.h"

class MouseEventData :
    public IEventData
{
public:
    MouseEventData(const Publisher sender, /*std::string Topic*/
        SDL_MouseButtonEvent MouseButton,
        SDL_MouseMotionEvent MousePositon,
        SDL_MouseWheelEvent MouseWheel);

    SDL_MouseButtonEvent mouseButton;
    SDL_MouseMotionEvent mousePositon;
    SDL_MouseWheelEvent mouseWheel;
};

