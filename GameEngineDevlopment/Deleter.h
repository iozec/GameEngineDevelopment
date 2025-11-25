#pragma once
#include "SDL3/SDL.h"
#include <memory>
#include "bitmap.h"

struct sdl_deleter
{
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }

};

