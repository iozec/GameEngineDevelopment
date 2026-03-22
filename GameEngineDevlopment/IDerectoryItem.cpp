#include "IDerectoryItem.h"
#include "ResourceManager.h"
#include "imGUI/imgui.h"
#include "IDerectoryItem.h"
#include "EditorGui.h"

IDirectoryItem::IDirectoryItem(
    std::shared_ptr<SDL_Texture> iconTexture,
    std::filesystem::directory_entry entery)
{
    IconTexture = iconTexture;
    Entery = entery;
}

std::shared_ptr<SDL_Texture> IDirectoryItem::GetTextureRef()
{
    return IconTexture;
}

const std::filesystem::directory_entry&
IDirectoryItem::GetDirectoryEntry() const
{
    return Entery;
}

bool IDirectoryItem::DrawIconButton()
{
    bool isClicked = false;
    ImGui::BeginChild(Entery.path().filename().string().c_str(), { 200,200 }, false);

    isClicked = ImGui::ImageButton("button", (ImTextureID)IconTexture.get(), { 100,100 });

    if (ImGui::BeginDragDropSource())
    {
        EditorGui::INSTANCE().AssetMouseDrag = this;
        ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", nullptr, 0);
        ImGui::Image((ImTextureID)IconTexture.get(), { 64, 64 });
        ImGui::Text("%s", Entery.path().filename().string().c_str());

        ImGui::EndDragDropSource();
    }
 

    ImGui::Text(Entery.path().filename().string().c_str());
    ImGui::EndChild();

    return isClicked;
}

void IDirectoryItem::OnClick()
{
}