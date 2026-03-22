// GameEngineDevlopment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "imGUI/backends/imgui_impl_sdl3.h"
#include "imGUI/backends/imgui_impl_sdlrenderer3.h"
#include "json.hpp"
#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Monster.h"
#include "Player.h"
#include "Input.h"
#include "debug.h"
#include "GameObject.h"
#include "BitmapComponent.h"
#include "ECS.h"
#include "RendererSystem.h"
#include "MovementSystem.h"
#include "StackArenaAllocator.h"
#include <random>
#include <iostream>
#include <fstream>

#include "sol/sol.hpp"
#include "ScriptComponent.h"
#include "EditorGui.h"
#include "Hierarchy.h"
#include "SaveLoadSystem.h"
#include "ProfilerSystem.h"
#include "Platform.h"
#include "AssetWindow.h"
//#include <imgui_widgets.cpp>

//void SavePlayerToJson(const Pawn& Player)
//{
//    nlohmann::json SaveData;
//
//    SaveData["Player"] = {
//        {"x", Player.GetX()},
//        {"y", Player.GetY()},
//
//    };
//
//    ////Write to file
//    std::ofstream file("savegame.json");
//    file << SaveData.dump(4); // Pretty print with 4 spaces
//    file.close();
//
//    std::cout << "Saved to savegame.json\n";
//
//};
//int LoadPlayerFromFjson(Pawn& Player)
//{
//    std::ifstream file("savegame.json");
//    if (!file.is_open())
//    {
//        std::cerr << "Failed to open savegame.json\n";
//        return -1;
//    }
//
//	nlohmann::json LoadData;
//
//    file >> LoadData;
//    file.close();
//
//    if(LoadData.contains("Player"))
//    {
//        Player.SetX(LoadData["Player"]["x"]);
//        Player.SetY(LoadData["Player"]["y"]);
//        std::cout << "Loaded from savegame.json\n";
//        return 0;
//    }
//    else
//    {
//        std::cerr << "invalid save data\n";
//        return -1;
//	}
//
//}

void DrawProfileData(ImGuiIO& io)
{
    ImGui::Begin("Profiler");

    static int selectedFrame = -1;
    static FrameMap* Snapshot;
    static std::vector<float>* FrameTimes;

    // take snapshot of all current frame data.
    if (ImGui::Button("take snapshot"))
    {
        Snapshot = &(ProfilerSystem::Instance().GetFrameData());
        FrameTimes = &(ProfilerSystem::Instance().GetFrameTimes());
    }

    ImGui::SameLine();
    static bool LiveFlameGraph = true;
    ImGui::Checkbox("Live Flame Graph", &LiveFlameGraph);
    if (LiveFlameGraph)
    {
        selectedFrame = -1;
    }
    static int range[2] = { 0, 100 };

    if (FrameTimes && FrameTimes->size() > 100)
    {
        ImGui::SliderInt2("Frame Range", range, 0, FrameTimes->size());

        if (range[0] == range[1])
            range[0] = range[1] - 1;

        std::vector<float> subData(
            FrameTimes->cbegin() + range[0],
            FrameTimes->cbegin() + range[1]
        );

        int tempHistSelection = ImGui::MyPlotHistogram(
            "Frame data",
            subData.data(),
            subData.size()
        );

        if (tempHistSelection != -1)
        {
            LiveFlameGraph = false;
            selectedFrame = tempHistSelection;
        }
    }

    FrameMap previousFrame = ProfilerSystem::Instance().GetLastFrameData();

    if (!LiveFlameGraph && selectedFrame != -1)
    {
        previousFrame.clear();

        for (auto& [SampleName, samples] : *Snapshot)
        {
            
            previousFrame[SampleName].push_back(samples[range[0] + selectedFrame]);
        }
    }
    else
    {
        LiveFlameGraph = true;
    }

    ImDrawList* drawList = ImGui::GetCurrentWindow()->DrawList;

    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // pos of screen top left
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas 

    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;

    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x,
        canvas_p0.y + canvas_sz.y);

    drawList->PushClipRect(canvas_p0, canvas_p1, true);

    uint64_t totalFrameTime = 0;
    std::vector<uint64_t> SampleTimes;
    std::vector<float> SampleWidths;
    std::vector<std::string> SampleNames;

    for (auto const& [SampleName, samples] : previousFrame)
    {
        totalFrameTime += samples[0].frameTime + 1;
        SampleTimes.push_back((uint64_t)samples[0].frameTime + 1);
        SampleNames.push_back(SampleName);
    }

    float MinBlockWidth = canvas_sz.x / totalFrameTime;   // GraphWindowWidth / totalFrameTime

    for (int i = 0; i < SampleTimes.size(); i++)
    {
        SampleWidths.push_back(SampleTimes[i] * MinBlockWidth);
    }

    ImGui::LabelText("Total Frame Time", std::to_string(totalFrameTime).c_str());
    ImGui::LabelText("Window Width / total frame time", std::to_string(MinBlockWidth).c_str());

    float TotalBlockWidthSoFar = 0;
    int sampleCount = previousFrame.size();

    const ImU32 col_outline_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF;
    const ImU32 col_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF;

    for (int i = 0; i < sampleCount; i++)
    {
        float ThisBlockWidth = SampleWidths[i];

      
        ImVec2 minPos(
            canvas_p0.x + TotalBlockWidthSoFar,
            canvas_p0.y + 100
        );

      
        ImVec2 maxPos(
            canvas_p0.x + TotalBlockWidthSoFar + ThisBlockWidth,
            canvas_p0.y + 200
        );

       
        drawList->AddRectFilled(
            minPos,
            maxPos,
            col_base,
            GImGui->Style.FrameRounding
        );

      
        drawList->AddRect(minPos, maxPos, col_outline_base);

        
        ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 10),SampleNames[i].c_str()
        );

      
        ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 25),std::to_string(SampleTimes[i] - 1).c_str()
        );

        TotalBlockWidthSoFar += ThisBlockWidth;
    }

    drawList->PopClipRect();

    ImGui::End();
}

int main(int argc, char* argv[])
{
/////
///// Stack arena allocator
/////
    StackArenaAllocator stack(1024); // 1 KB stack allocator

    // Vector backed by stack allocator
    std::pmr::vector<int> numbers(&stack);
    for (int i = 0; i < 10; ++i)
        numbers.push_back(i * 10);

    std::cout << "Numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    // String backed by same stack allocator
    std::pmr::string msg("Hello from StackArena!", &stack);
    std::cout << msg << "\n";

    // Free everything at once
    std::cout << "Resetting stack...\n";
    stack.reset();

    ///////Renderer Setup////////
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME", 1000, 1000, 0);
    SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED);
    std::shared_ptr<SDL_Renderer> rendere =
        std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(win, NULL), sdl_deleter());
    SDL_Color backgroundColor = { 0, 100, 200, 255 };
    SDL_SetRenderDrawColor(rendere.get(), 0, 100, 200, 0);
    std::shared_ptr<SDL_Renderer> Rendere = std::shared_ptr<SDL_Renderer>(rendere);

	Hierarchy::INSTANCE().Init(Rendere);

    //Sprites
      //RendererSystem::AddBitmapComponentToEntity(0, ecs,
       // "./../Assets/monster.bmp", rendere, false);
   // MovementSystem::AddPositonComponentToEntitiy(0, ecs, 400, 400);
//MovementSystem::AddVelocityComponentToEntitiy(0, ecs, 5, 0, 0);

    ECS ecs;
 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);
  
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        RendererSystem::AddBitmapComponentToEntity(i, ecs,
            "./../assets/monstertrans.bmp", rendere, true);
        MovementSystem::AddPositonComponentToEntitiy(i, ecs, 100, 400);
        float RandomX = dist(gen);
        MovementSystem::AddVelocityComponentToEntitiy(i, ecs, RandomX, -30, 1);
    } 
    

    //////////////////////////////LUA INTEGRATION//////////////////////////////////

    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // Load Lua script
    lua.script_file("./../luaSrc/Enemy.lua");

    // Bind Player so Lua can interact with it (if needed later)
    lua.new_usertype<Player>("Player",
        "health", &Player::health,
        "takeDamage", &Player::takeDamage
    );

    // Get enemy table from Lua
    sol::table enemy = lua["enemy"];
    std::string name = enemy["name"];
    int enemyHealth = enemy["health"];

    std::cout << "Enemy spawned: " << name << " with " << enemyHealth << " HP\n";

    Player player1(rendere,
        "./../Assets/monster.bmp",
        100, 200, false);

    // Call enemy.attack(Player.health)
    sol::function attackFunc = enemy["attack"];
    int newPlayerHealth = attackFunc(player1.health);
    player1.health = newPlayerHealth;

    // Call enemy.onDamage(12)
    sol::function onDamageFunc = enemy["onDamage"];
    onDamageFunc(12);

    /////////////////////////////////end lua integration/////////////////////////////////

        Player player(Rendere,
        "./../assets/monster.bmp", 100, 200, true);
        Monster monster(Rendere,
        "./../assets/monstertrans.bmp", 200, 200, true);
        Platform platform(Rendere,
            "./../assets/Platform.png", 200, 700, true);


        GameObject gameObject;

        gameObject.transform.SetX(400);
        gameObject.transform.SetY(400);

        std::shared_ptr<BitmapComponent> temp = std::make_shared<BitmapComponent>(
            rendere, "./../Assets/monstertrans.bmp", 300, 200, true, &gameObject);
        gameObject.AddComponent(temp);
        std::shared_ptr<ScriptComponent> scriptTest = std::make_shared<ScriptComponent>(
            "./../luaSrc/EnemyScr.lua", &gameObject);
        gameObject.AddComponent(scriptTest);

        monster.Subscribe("MouseButtonUpdate");
        monster.Subscribe("MousePositionUpdate");
        monster.Subscribe("MouseWheelUpdate");

        player.Subscribe("MousePositionUpdate");
        player.Subscribe("MouseWheelUpdate");
        player.Subscribe("MouseButtonUpdate");

        Hierarchy::INSTANCE().AddPawn(&player);
        Hierarchy::INSTANCE().AddPawn(&monster);
        Hierarchy::INSTANCE().AddPawn(&platform);

        monster.Subscribe("Test");

    BitmapComponent* temp2 = gameObject.GetComponentByType<BitmapComponent>();

    bool IsRunning = true;

    Input in;
    VerboseDebugPrintF(Verbosity::Error,
        "UOSGameEngine started with %d arguments\n", argc);

    //////////////////////
// ImGUI
//////////////////////

// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;


    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(win, rendere.get());
    ImGui_ImplSDLRenderer3_Init(rendere.get());

    AssetWindow* assetWindow = new AssetWindow(rendere);



    while (IsRunning)
    {
        ProfilerSystem::Instance().StartFrame();

        // INPUT & EVENTS
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            Input::INSTANCE().UpdateMouse(e);
            ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {
            case SDL_EVENT_QUIT:
                IsRunning = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (e.key.scancode == SDL_SCANCODE_0)
                    SaveLoadSystem::INSTANCE().SaveGame("SavegameGO.json", gameObject);
                else if (e.key.scancode == SDL_SCANCODE_P)
                    SaveLoadSystem::INSTANCE().LoadGame("SavegameGO.json", gameObject, rendere);
                break;
            }
        }
        Input::INSTANCE().UpdateKeyBoard();

        // LOGIC & PHYSICS UPDATES
        // Update ECS systems
        MovementSystem::UpdatePositions(ecs);

        // Update Hierarchy Pawns (Includes player, monster, and dragged platforms)
        for (Pawn* p : Hierarchy::INSTANCE().GetHierarchyList()) {
            p->Update();
        }

        // Update independent GameObjects
        gameObject.Update();

        // Logic for Grounded state
        int oldY = player.Position.y;

        if (player.Position.y == oldY + player.DeltaMove.y && player.DeltaMove.y > 0)
            player.Grounded = false;
        else if (player.DeltaMove.y >= 0)
            player.Grounded = (player.Position.y < oldY + player.DeltaMove.y);

        // IMGUI FRAME START
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // RENDERING
        // Clear Screen
        SDL_SetRenderDrawColor(rendere.get(), backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        SDL_RenderClear(rendere.get());

        // Draw ECS Entities
        RendererSystem::Render(ecs, rendere);

        // Draw Hierarchy and World Objects
        {
            PROFILE("WorldRender");
 
            Hierarchy::INSTANCE().DrawHierarchyItems();
        }

        // Draw Editor/UI Windows
        DrawProfileData(io);
        EditorGui::INSTANCE().DrawWindows();
        Hierarchy::INSTANCE().Draw();
        EditorGui::INSTANCE().DrawWindow();
        assetWindow->DrawWindow();
        ImGui::ShowDemoWindow();

        // Finalize ImGui and Swap Buffers
        ImGui::Render();
        SDL_SetRenderScale(rendere.get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), rendere.get());

        // PRESENT (Only once)
        SDL_RenderPresent(rendere.get());

        Input::INSTANCE().LateUpdate();
        SDL_Delay(16);
        ProfilerSystem::Instance().EndFrame();
    } // end of main loop
    ProfilerSystem::Instance().WriteDataToCSV();



    //SDL_DestroyRenderer(rendere);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
