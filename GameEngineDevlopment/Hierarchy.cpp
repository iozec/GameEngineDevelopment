#include "Hierarchy.h"
#include "EditorGui.h"


Hierarchy* Hierarchy::_instance = nullptr;

const std::vector<Pawn*>& Hierarchy::GetHierarchyList() const
{
       return HierarchyList;
}

Hierarchy& const Hierarchy::INSTANCE()
{
    if (!Hierarchy::_instance)
        Hierarchy::_instance = new Hierarchy();

    return *Hierarchy::_instance;
}

Pawn* Hierarchy::AddGameObject(const std::string path, int x, int y, bool isTransparent)
{
    Pawn* newPawn = new Pawn(renderer, path, x, y, isTransparent);
    HierarchyList.push_back(newPawn);
    return newPawn;
}

void Hierarchy::DrawHierarchyItems()
{
    for (int i = 0; i < HierarchyList.size(); i++)
    {
        HierarchyList[i]->Draw();
    }
}

void Hierarchy::DrawPawnNode(Pawn* pawn, ImGuiTreeNodeFlags nodeFlags)
{
    // Tree node for this pawn
    bool isNodeOpen = ImGui::TreeNodeEx(
        std::to_string(pawn->ID).c_str(),
        nodeFlags,
        "%d",
        pawn->ID
    );

    // Click selection
    if (ImGui::IsItemClicked())
    {
        std::cout << "selected object is " << pawn->ID << std::endl;
    }

    // Drag source
    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("TREENODE", pawn, sizeof(Pawn));
        ImGui::Text("This is a drag and drop source");
        ImGui::EndDragDropSource();
    }


    if (isNodeOpen)
    {
        for (int i = 0; i < 5; ++i)
        {
            std::string itemName = "Child " + std::to_string(i);
            if (ImGui::TreeNodeEx(
                itemName.c_str(),
                nodeFlags,
                "%s",
                itemName.c_str()))
            {
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}

void Hierarchy::AddPawn(Pawn* pawn)
{
    HierarchyList.push_back(pawn);
}

void Hierarchy::Draw()
{
    ImGui::Begin("Hierarchy");


    ImGuiTreeNodeFlags nodeFlags =
        ImGuiTreeNodeFlags_FramePadding |
        ImGuiTreeNodeFlags_DefaultOpen;


    const std::vector<Pawn*>& hierarchy = Hierarchy::INSTANCE().GetHierarchyList();


    for (Pawn* pawn : hierarchy)
    {
        DrawPawnNode(pawn, nodeFlags);
    }

    // Mouse check hover
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TREENODE"))
        {
            IM_ASSERT(payload->DataSize == sizeof(Pawn));
            Pawn* payloadAsPawn = static_cast<Pawn*>(payload->Data);
            std::cout << payloadAsPawn->ID << " on top of Root" << std::endl;
        }

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        {
            auto droppedItem = EditorGui::INSTANCE().AssetMouseDrag;

            if (droppedItem)
            {
                std::string path = droppedItem->GetDirectoryEntry().path().string();

                AddGameObject(path, 0, 0, true);

                std::cout << "Added new Pawn to Hierarchy from path: " << path << std::endl;
            }
        }



        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}
