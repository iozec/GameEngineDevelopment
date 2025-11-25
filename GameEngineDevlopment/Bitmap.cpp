#include "Bitmap.h"

Bitmap::Bitmap(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent)
{ 
	_renderer = renderer;
	_xPosition = x;
	_yPosition = y;

	//Load surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		SDL_Log("Unable to load image %s! SDL_inage error: %s\n", path.c_str(),
			SDL_GetError());
	}
	else
	{

		if (isTransparent)
		{
			Uint32 colourKey = SDL_MapSurfaceRGBA(loadedSurface, 255, 0, 255, 0);
			SDL_SetSurfaceColorKey(loadedSurface, true, colourKey);

		}

		SDL_Texture* tempTex = SDL_CreateTextureFromSurface(
			_renderer.get(), loadedSurface);
		_texture = std::unique_ptr<SDL_Texture, sdl_deleter>(tempTex, sdl_deleter());
		 

		if (_texture == nullptr)
		{
			SDL_Log("Unable to create texture from loaded pixels! SD: error: %s\n",
				SDL_GetError());
		}
		else
		{

			//get image Dimentions
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}
		//Clean up loaded surface
		SDL_DestroySurface(loadedSurface);

		


	}

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