#include "Monster.h"
#include <iostream>
#include "Message.h"
#include "GameObject.h"

Monster::Monster(std::shared_ptr<SDL_Renderer> renderer,
    const std::string path, int x, int y, bool isTransparent) :
    Pawn(renderer, path, x, y, isTransparent)
{

    this->ObjectType = GameObject::ObjectTypes::Enemy;
    this->m_IsActive = true;

   
    m_startX = x;
    m_walkRange = 200;
    m_direction = 1;   
    speed = 2;         
}

void Monster::Update()
{
  
    int movement = speed * m_direction;

  
    Position.x += movement;

   
    if (Position.x >= m_startX + m_walkRange)
    {
        Position.x = m_startX + m_walkRange; 
        m_direction = -1;                   
    }
    else if (Position.x <= m_startX)
    {
        Position.x = m_startX;              
        m_direction = 1;               
    }

    Pawn::Update();
}

