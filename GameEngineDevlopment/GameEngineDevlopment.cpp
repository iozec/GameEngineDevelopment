// GameEngineDevlopment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Monster.h"
#include "Player.h"
#include "Input.h"



int main(int argc, char* argv[])
{
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

    Player player(Rendere,
        "./../assets/monster.bmp", 100, 200, false);
    Monster monster(Rendere,
        "./../assets/monstertrans.bmp", 200, 200, true);

    bool IsRunning = true;

    while (IsRunning)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))

            Input::INSTANCE().Update();
        if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP))
            player.UpdatePosition(0, -1);

            SDL_RenderClear(Rendere.get());
            player.Draw();
            monster.Draw();
            SDL_RenderPresent(Rendere.get());

            Input::INSTANCE().LateUpdate();

            SDL_Delay(16);
            //void Update();
        

    }

    Input in;




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
