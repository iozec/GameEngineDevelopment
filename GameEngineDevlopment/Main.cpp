// GameEngineDevlopment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "imGui.h"
#include "imGUI/backends/imgui_impl_sdl3.h"
#include "imGUI/backends/imgui_impl_sdlrenderer3.h"
#include <iostream>
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
#include <random>
#include "StackArenaAllocator.h"

#include "sol/sol.hpp"
#include "ScriptComponent.h"
#include "EditorGui.h"




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
        GameObject gameObject;


        gameObject.transform.SetX(400);
        gameObject.transform.SetY(400);

        std::shared_ptr<BitmapComponent> temp = std::make_shared<BitmapComponent>(
            rendere, "./../Assets/monstertrans.bmp", 300, 200, true, &gameObject);
        gameObject.AddComponent(temp);
        std::shared_ptr<ScriptComponent> scriptTest = std::make_shared<ScriptComponent>(
            "./../luaSrc/ComponentTest.lua", &gameObject);
        gameObject.AddComponent(scriptTest);

        monster.Subscribe("MouseButtonUpdate");
        monster.Subscribe("MousePositionUpdate");
        monster.Subscribe("MouseWheelUpdate");

        player.Subscribe("MousePositionUpdate");
        player.Subscribe("MouseWheelUpdate");
        player.Subscribe("MouseButtonUpdate");


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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    style.ScaleAllSizes(main_scale);     // Bake a fixed style scale.
    // (Until we have a solution for dynamic style scaling, changing this
    // requires resetting style + calling this again)
    style.FontScaleDpi = main_scale;     // Set initial font scale.
    // (Using io.ConfigFlags |= ImGuiConfigFlags_DpiScaleFonts = true makes this unnecessary.
    // We leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(win, rendere.get());
    ImGui_ImplSDLRenderer3_Init(rendere.get());

    //////////////////////
    // ImGUI
    //////////////////////

    while (IsRunning)
    {


        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            Input::INSTANCE().UpdateMouse(e);
            ImGui_ImplSDL3_ProcessEvent(&e);
            switch (e.type) {

            case SDL_EVENT_QUIT:
                IsRunning = false;
                break;

            default:
                break;
            }
        }

        Input::INSTANCE().UpdateKeyBoard();
        /*if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP))
            player.UpdatePosition(0, -1);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_DOWN))
            player.UpdatePosition(0, 1);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_LEFT))
            player.UpdatePosition(-1, 0);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_RIGHT))
            player.UpdatePosition(1, 0);*/

        // Update background color based on input
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_1))
            backgroundColor = { 255, 0, 0, 255 };

        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_2))
            backgroundColor = { 0, 255, 0, 255 };

        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_3))
            backgroundColor = { 0, 0, 255, 255 };

        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_4))
            backgroundColor = { 0, 100, 200, 128 };

        

            SDL_RenderClear(rendere.get());

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            EditorGui::INSTANCE().DrawWindows();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()!
            // You can browse its code to learn more about Dear ImGui).
            ImGui::ShowDemoWindow();

			ImGui::Begin("the First Window");      // Create a window called "Hello, world!" and append into it.)
            if (ImGui::Button("Press me"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                std::cout << "Button Pressed" << std::endl;

            static float test[2];
			ImGui::InputFloat2("Test Input float", test);
            ImGui::End();

            MovementSystem::UpdatePositions(ecs);
            RendererSystem::Render(ecs, rendere);
            gameObject.Update();

            
            //player.DrawCollider(player.GetCollisionBounds());
            player.Update();

            int oldY = player.Position.y;

            player.IsOverlapping(monster, player.DeltaMove);

            if (player.Position.y == oldY + player.DeltaMove.y && player.DeltaMove.y > 0)
                player.Grounded = false;
            else if (player.DeltaMove.y >= 0)
                player.Grounded = (player.Position.y < oldY + player.DeltaMove.y);   // hit ground
            player.Draw();

            monster.Draw();
            //monster.DrawCollider(monster.GetCollisionBounds());
            // 
            // Rendering
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGui::Render();
            SDL_SetRenderScale(rendere.get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColorFloat(rendere.get(), clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), rendere.get());

            SDL_RenderPresent(rendere.get());

            SDL_RenderPresent(rendere.get());


            Input::INSTANCE().LateUpdate();

            SDL_Delay(16);
            //void Update();
        

    }






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
