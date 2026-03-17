#pragma once
#include <string>
#include <memory>
#include <filesystem>

struct SDL_Texture;

class IDirectoryItem
{
protected:
    std::shared_ptr<SDL_Texture> IconTexture;
    std::filesystem::directory_entry Entery;
private:
public:
    IDirectoryItem(std::shared_ptr<SDL_Texture> iconTexture,
        std::filesystem::directory_entry entery);
    ~IDirectoryItem() = default;
    void OnClick();
    bool DrawIconButton();

    std::shared_ptr<SDL_Texture> GetTextureRef();
    const std::filesystem::directory_entry& GetDirectoryEntry() const;
};

