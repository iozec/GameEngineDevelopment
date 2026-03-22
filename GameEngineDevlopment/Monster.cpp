#include "Monster.h"
#include <iostream>
#include "Message.h"
#include "GameObject.h"

Monster::Monster(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent) :
	Pawn(renderer, path, x, y, isTransparent)
{
}

