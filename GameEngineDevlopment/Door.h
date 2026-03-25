#pragma once
#pragma once
#include "Pawn.h"
class Door : public Pawn
{
public:

	Door(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);


};


