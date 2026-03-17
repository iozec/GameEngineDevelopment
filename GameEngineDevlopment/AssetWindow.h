#pragma once
#include "IGuiWindow.h"
#include "IDerectoryItem.h"
#include <stack>
#include "SDL3/SDL.h"

struct SDL_Renderer;
struct SDL_Texture;
class Bitmap;

class AssetWindow :
    public IGuiWindow
{
public:
    AssetWindow(const std::shared_ptr<SDL_Renderer>& pRenderer);
    ~AssetWindow();
    void DrawWindow() override;
    void GetItemsInDirectory();


private:
    std::vector<IDirectoryItem*> content;
    std::stack<std::filesystem::path> dirStack;
    std::shared_ptr<SDL_Texture> BackButtontexture;
    std::shared_ptr<SDL_Renderer> renderer;

};

