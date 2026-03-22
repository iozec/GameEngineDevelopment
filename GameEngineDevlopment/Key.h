#pragma once
#include "Pawn.h"
class Key : public Pawn
{
public:

	Key(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);
};

