#pragma once
#include "I_ComponentBase.h"
#include <memory>
#include "bitmap.h"
class BitmapComponent :
	public I_ComponentBase
{
	std::shared_ptr<Bitmap> _bitmap;

public:
	BitmapComponent(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent, GameObject* parent);
		
	
	~BitmapComponent() override {};
	void Update() override;
};



