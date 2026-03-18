#include "Bitmap.h"
#include "ResourceManager.h"	
#include "Pawn.h"
Bitmap::Bitmap(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent)
{ 
	_renderer = renderer;
	_xPosition = x;
	_yPosition = y;

	float w, h;
	//Got texture width and height
	_texture = ResourceManager::INSTANCE().LoadTexture(path,
		isTransparent, _renderer);
	SDL_GetTextureSize(_texture.get(), &w, &h);
	_width = w;
	_height = h;

	this->path = path;
}

SDL_Rect Bitmap::GetImageBounds() const
{
	SDL_Rect a = { _xPosition, _yPosition, _width, _height };
	return a;
}

std::shared_ptr<SDL_Renderer> Bitmap::GetRenderer() const
{
	return _renderer;
}



void Bitmap::Draw()
{
	Draw(_xPosition, _yPosition);
}

void Bitmap::Draw(int x, int y)
{
	//Set texture position
	SDL_FRect dstRect = { x, y, _width, _height };

	//render texture
	SDL_RenderTexture(_renderer.get(), _texture.get(), NULL, &dstRect);
}