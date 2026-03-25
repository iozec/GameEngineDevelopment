#pragma once
#include "Pawn.h"

class Monster : public Pawn
{
private:
    int m_startX;      
    int m_walkRange;  
    int m_direction;   

public:
    Monster(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent);

   
    void Update() override;
};

