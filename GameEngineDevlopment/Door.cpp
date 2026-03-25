#include "Door.h"

Door::Door(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent) : Pawn(renderer, path, x, y, isTransparent)
{
	this->ObjectType = GameObject::ObjectTypes::Door;
	this->m_IsActive = true;
}
