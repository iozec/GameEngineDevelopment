#include "SaveLoadSystem.h"
#include "GameObject.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

SaveLoadSystem* SaveLoadSystem::_instance = nullptr;

SaveLoadSystem& SaveLoadSystem::INSTANCE()
{
    if (!_instance)
        _instance = new SaveLoadSystem();
    return *_instance;
}

void SaveLoadSystem::SaveGame(const std::string& filename,
    const GameObject& ToSave)
{
    nlohmann::json saveData = ToSave.Save();

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not save to file: " << filename << "\n";
        return;
    }

    file << saveData.dump(4);
    file.close();
}

void SaveLoadSystem::LoadGame(const std::string& filename,
    GameObject& ToLoad,
    std::shared_ptr<SDL_Renderer> renderer)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Could not load file: " << filename << "\n";
        return;
    }

    nlohmann::json loadData;
    file >> loadData;
    file.close();

    ToLoad.Load(loadData, renderer);
}