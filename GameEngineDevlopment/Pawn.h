#pragma once
#include <memory>
#include <string>
#include "SDL3/SDL.h"
#include "Bitmap.h"
#include "Subscriber.h"
#include "Publisher.h"
#include "IGuiWindow.h"

class Broker;

class Pawn : public Publisher, public Subscriber, public IGuiWindow
{
protected:
    std::unique_ptr<Bitmap> Sprite;
    Broker* broker; 

public:
    Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path,
        int x, int y, bool isTransparent );

    int ID = 0;
	static int CurrentID;

    void Receive(const IEventData* message, const std::string& topic) override;
    void SetDeltaMove(int x, int y);
    bool IsOverlapping(const Pawn& Other, const SDL_Point& Delta);

    virtual ~Pawn() {}

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
};




