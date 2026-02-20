// GameEngineDevlopment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



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
            "./../assets/monster.bmp", rendere, true);
        MovementSystem::AddPositonComponentToEntitiy(i, ecs, 100, 400);
        float RandomX = dist(gen);
        MovementSystem::AddVelocityComponentToEntitiy(i, ecs, RandomX, -30, 1);
    } 
    Broker* broker = Broker::Instance();

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
        100, 200, false, *broker);

    // Call enemy.attack(Player.health)
    sol::function attackFunc = enemy["attack"];
    int newPlayerHealth = attackFunc(player1.health);
    player1.health = newPlayerHealth;

    // Call enemy.onDamage(12)
    sol::function onDamageFunc = enemy["onDamage"];
    onDamageFunc(12);

    /////////////////////////////////end lua integration/////////////////////////////////

    Player player(Rendere,
        "./../assets/monster.bmp", 100, 200, false, *broker);
        Monster monster(Rendere,
        "./../assets/monstertrans.bmp", 200, 200, true, *broker);
        GameObject gameObject;
        std::shared_ptr<BitmapComponent> temp = std::make_shared<BitmapComponent>(
            rendere, "./../Assets/monster.bmp", 300, 200, false);
        gameObject.AddComponent(temp);

        monster.Subscribe("Test");

    BitmapComponent* temp2 = gameObject.GetComponentByType<BitmapComponent>();

    bool IsRunning = true;

    Input in;

    VerboseDebugPrintF(Verbosity::Error,
        "UOSGameEngine started with %d arguments\n", argc);



    while (IsRunning)
    {


        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                IsRunning = false;
            }
        }

        Input::INSTANCE().Update();
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP))
            player.UpdatePosition(0, -1);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_DOWN))
            player.UpdatePosition(0, 1);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_LEFT))
            player.UpdatePosition(-1, 0);
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_RIGHT))
            player.UpdatePosition(1, 0);

            SDL_RenderClear(rendere.get());
            RendererSystem::Render(ecs, rendere);
            MovementSystem::UpdatePositions(ecs);
            gameObject.Update();
            player.Draw();
            monster.Draw();
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
