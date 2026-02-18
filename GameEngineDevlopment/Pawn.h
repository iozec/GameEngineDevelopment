#pragma once
#include <memory>
#include <string>
#include "SDL3/SDL.h"
#include "Bitmap.h"

class Broker;

class Pawn {
protected:
    int X = 0; 
    int Y = 0;
    std::unique_ptr<Bitmap> Sprite;
    Broker* broker; 

public:
    Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path,
        int x, int y, bool isTransparent, Broker& broker);

    virtual ~Pawn() {}

    void UpdatePosition(int x, int y);
    void Draw();

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);

    virtual void Update();
};




