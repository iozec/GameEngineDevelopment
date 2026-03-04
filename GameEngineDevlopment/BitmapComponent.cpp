#include "BitmapComponent.h"
#include "GameObject.h"
BitmapComponent::BitmapComponent(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, GameObject* parent)
	: I_ComponentBase(parent)
{
	_bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
}


void BitmapComponent::Update()
{
    if (_bitmap && ParentObject)
    {
     
        int x = ParentObject->transform.GetX();
        int y = ParentObject->transform.GetY();

        
        _bitmap->Draw(x, y);
    }
}