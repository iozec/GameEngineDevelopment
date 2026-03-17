#include "AssetWindow.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <imgui.h>
#include "ResourceManager.h"
#include "SDL3_image/SDL_image.h"

AssetWindow::AssetWindow(const std::shared_ptr<SDL_Renderer>& pRenderer)
{
    ////////////////////////////////
    // Read files in assets folder//
    ////////////////////////////////

    BackButtontexture = ResourceManager::INSTANCE().LoadTexture(
        "./../Assets/SVG/left-arrow-svgrepo-com.png", true, pRenderer);

    std::string path = "../../Assets";
    std::filesystem::path dirPath(path);
    dirStack.push(dirPath);

    renderer = pRenderer;

    GetItemsInDirectory();

   
  }


    void AssetWindow::DrawWindow()
    {
        ImGui::Begin("Assets");

        if (ImGui::ImageButton("button", (ImTextureID)BackButtontexture.get(), { 64, 64 }))
        {
            if (dirStack.size() > 1)
            {
                dirStack.pop();
                GetItemsInDirectory();
            }
        }

        ImGui::BeginChild("Content Window", ImVec2(), true);
        ImGui::BeginTable("Content browser", 3);

        for (int i = 0; i < content.size(); i++)
        {
            ImGui::SameLine();
            ImGui::PushID(i);

            if (content[i]->DrawIconButton())
            {
                if (content[i]->GetDirectoryEntry().is_directory())
                {
                    dirStack.push(content[i]->GetDirectoryEntry().path());
                }
                else
                {
                    content[i]->OnClick();
                }
            }
            //////////////////////////////// For Dragging
            if (ImGui::BeginDragDropSource())
            {
                //AssetMouseDrag = content[i];
                ImGui::Image((ImTextureID)content[i]->GetTextureRef().get(), { 100,100 });
                ImGui::EndDragDropSource();
            }
            //////////////////////////////// For Dragging

            ImGui::PopID();
            ImGui::SameLine();
        }

        ImGui::EndTabItem();

        ImGui::EndChild();

        ImGui::End();

 
        Bitmap* AssetMouseDrag = nullptr;


}

    void AssetWindow::GetItemsInDirectory()
    {
        content.clear();
        std::filesystem::path dirPath = dirStack.top();

        for (const auto& entry : std::filesystem::directory_iterator(dirPath))
        {
            if (entry.path().extension() == ".bmp" ||
                entry.path().extension() == ".jpg" ||
                entry.path().extension() == ".png")
            {
                IDirectoryItem* File = new IDirectoryItem(
                    ResourceManager::INSTANCE().LoadTexture(entry.path().string(), true, renderer),
                    entry);
                content.push_back(File);
            }
            else if (entry.path().extension() == ".svg")
            {
                IDirectoryItem* File = new IDirectoryItem(
                    ResourceManager::INSTANCE().LoadSVGTexture(entry.path().string().c_str(), 64, 64),
                    entry);
                content.push_back(File);
            }
            else if (entry.is_directory())
            {
                IDirectoryItem* Dir = new IDirectoryItem(
                    ResourceManager::INSTANCE().LoadSVGTexture("./Assets/SVG/FOLDER.svg", 64, 64),
                    entry);
                content.push_back(Dir);
                std::cout << "dir << " << entry << std::endl;
            }
            else
            {
                IDirectoryItem* File = new IDirectoryItem(
                    ResourceManager::INSTANCE().LoadSVGTexture("./Assets/SVG/EMPTY BLANK.svg", 64, 64),
                    entry);
                content.push_back(File);
            }

            std::cout << entry.path() << std::endl;
        }
    }


    AssetWindow::~AssetWindow()
    {
        for (int i = 0; i < content.size(); i++)
        {
            delete content[i];
        }
    }