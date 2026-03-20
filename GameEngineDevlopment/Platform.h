#pragma once
#include "Pawn.h"
class Platform : public Pawn
{
public:

	Platform(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);
};

