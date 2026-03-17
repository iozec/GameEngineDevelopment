#pragma once

#include <map>
#include <string>
#include <memory>
#include "SDL3/SDL.h"

class ResourceManager
{
public: 
	std::shared_ptr<SDL_Texture> LoadTexture(std::string FilePath,
		bool isTransparent, 
		std::shared_ptr<SDL_Renderer> renderer);
	//std::shared_ptr<SDL_Renderer> renderer;
	static ResourceManager* _instance;
	static ResourceManager& INSTANCE();
	std::shared_ptr<SDL_Texture> LoadSVGTexture(const char* filename, int width, int height);

	~ResourceManager();

private:
	std::map<std::string,
		std::shared_ptr<SDL_Texture>> TextureMap;


};

