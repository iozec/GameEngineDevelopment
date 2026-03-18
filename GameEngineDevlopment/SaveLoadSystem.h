#pragma once
#include <memory>
#include <string>

class GameObject;
struct SDL_Renderer;

class SaveLoadSystem
{
public:
    static SaveLoadSystem* _instance;
    static SaveLoadSystem& INSTANCE();

    void SaveGame(const std::string& filename, const GameObject& ToSave);
    void LoadGame(const std::string& filename,
        GameObject& ToLoad,
        std::shared_ptr<SDL_Renderer> renderer);
};


