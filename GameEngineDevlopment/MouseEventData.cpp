#include "MouseEventData.h"
#include "Publisher.h"

MouseEventData::MouseEventData(const Publisher sender, /*std::string Topic*/
	SDL_MouseButtonEvent MouseButton,
	SDL_MouseMotionEvent MousePositon,
	SDL_MouseWheelEvent MouseWheel) :
	IEventData(sender),
	mouseButton(MouseButton),
	mousePositon(MousePositon),
	mouseWheel(MouseWheel)
{
}