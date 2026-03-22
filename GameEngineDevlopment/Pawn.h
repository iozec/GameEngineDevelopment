#pragma once
#include <memory>
#include <string>
#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Subscriber.h"
#include "Publisher.h"
#include "IGuiWindow.h"
#include "GameObject.h"

class Broker;

class Pawn : public Subscriber, public IGuiWindow, virtual public GameObject
{
protected:
    std::unique_ptr<Bitmap> Sprite;
    Broker* broker; 

public:
    Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path,
        int x, int y, bool isTransparent );

    virtual ~Pawn() {}

    int ID = 0;
	static int CurrentID;
    bool isDragging = false;
    SDL_Point dragOffset = { 0, 0 };

    void Receive(const IEventData* message, const std::string& topic) override;
    void SetDeltaMove(int x, int y);
    bool IsOverlapping(const Pawn& Other, const SDL_Point& Delta);
    std::string GetPath() const { return filePath; }
    
    

    SDL_Rect GetCollisionBounds() const;
    void DrawCollider(SDL_Rect Collider) const;

	void DrawWindow() override;
    void UpdatePosition(int x, int y);
    void Draw();

    int GetX();
    void SetX(int x);
    int GetY();
    void SetY(int y);

    virtual void Update();

    int speed = 1;
	int gravity = 1;
	int maxFallSpeed = 10;
    bool Grounded = false;

    SDL_Point Position;
    SDL_Point DeltaMove;
private :

    std::string filePath;
};




