#include "Key.h"

Key::Key(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent) : Pawn(renderer, path, x, y, isTransparent)
{
	this->ID = 99;
	this->m_IsActive = true;
}
