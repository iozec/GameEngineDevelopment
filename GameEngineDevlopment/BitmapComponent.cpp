#include "BitmapComponent.h"
#include "GameObject.h"
BitmapComponent::BitmapComponent(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, GameObject* parent)
	: I_ComponentBase(parent)
{
	_bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
}


BitmapComponent::BitmapComponent(GameObject* parentObject)
    : I_ComponentBase(parentObject) {}


void BitmapComponent::Update()
{
    if (_bitmap && ParentObject)
    {
     
        int x = ParentObject->transform.GetX();
        int y = ParentObject->transform.GetY();

        
        _bitmap->Draw(x, y);
    }
}

nlohmann::json BitmapComponent::Save() const
{
    nlohmann::json BitmapSaveData;

    BitmapSaveData[Type()] = {
        { "path",         _bitmap->GetPath() },
        { "x",            _bitmap->GetX() },
        { "y",            _bitmap->GetY() },
        { "isTransparent", _bitmap->GetIsTransparent() },
        { "width",        _bitmap->GetWidth() },
        { "height",       _bitmap->GetHeight() },
        { "type",         Type() }
    };

    return BitmapSaveData;
}

void BitmapComponent::Load(nlohmann::json LoadData, std::shared_ptr<SDL_Renderer> renderer)
{
    const std::string path = LoadData["path"].get<std::string>();
    int x = LoadData["x"];
    int y = LoadData["y"];
    bool isTransparent = LoadData["isTransparent"];

    _bitmap = std::make_shared<Bitmap>(renderer, path, x, y, isTransparent);
}
