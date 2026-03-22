#pragma once
#include "imgui.h"
#include <memory>
#include <string>
#include <vector>
#include <imgui.h>
#include <iostream>


#include "Pawn.h"

    class SDL_Renderer;

    class Hierarchy
    {
        std::shared_ptr<SDL_Renderer> renderer;
    public:

        void Init(const std::shared_ptr<SDL_Renderer>& rendererPtr)
        {
            renderer = rendererPtr;
        }

        const std::vector<Pawn*>& GetHierarchyList() const;


        Hierarchy() {};

       
        static Hierarchy* _instance;
        static Hierarchy& const INSTANCE();

        std::vector<Pawn*> HierarchyList;

        Pawn* AddGameObject(const std::string path, int x, int y, bool isTransparent);

        void Draw();

        void DrawHierarchyItems();

        void DrawPawnNode(Pawn* pawn, ImGuiTreeNodeFlags nodeFlags);

        void AddPawn(Pawn* pawn);

    };
