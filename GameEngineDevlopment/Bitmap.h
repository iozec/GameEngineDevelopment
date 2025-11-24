#pragma once

#include "SDL3/SDL.h"
#include <memory>
#include <string>
#include "SDL3_image/SDL_image.h"
class Bitmap
{
public:

	Bitmap(
		std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);

	void Draw();
	void Draw(int x, int y);
private:
	std::shared_ptr<SDL_Renderer > _renderer;
	int _xPosition;
	int _yPosition;
	int _width;
	int _height;

	std::unique_ptr<SDL_Texture> _texture;
};


