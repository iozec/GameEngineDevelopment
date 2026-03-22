#include "Player.h"
#include "Input.h"
#include "Message.h"
#include "Hierarchy.h"

Player::Player(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent) :
	Pawn(renderer, path, x, y, isTransparent)
	
{
}

void Player::Update() {

	DeltaMove.x = 0;
	DeltaMove.y = 0;

	Input::INSTANCE().UpdateKeyBoard();
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP)) {
		UpdatePosition(0, -speed);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_DOWN)) {
		UpdatePosition(0, speed);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_LEFT)) {
		UpdatePosition(-speed, 0);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_RIGHT)) {
		UpdatePosition(speed, 0);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_P)) {

		Publish("Test", new Message(*this, "<Test message>"));
	}

	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_SPACE)) {

		DeltaMove.y = -15;
		Grounded = false;
	}

	DeltaMove.y += gravity;

	DeltaMove.y = std::min(DeltaMove.y, maxFallSpeed);

	bool isTouchingSomething = false;

	for (Pawn* platform : Hierarchy::INSTANCE().GetHierarchyList())
	{
	
		if (platform == this) continue;

		
		if (this->IsOverlapping(*platform, DeltaMove))
		{
		
			if (DeltaMove.y > 0)
			{
				this->Grounded = true;
				this->Position.y = platform->GetCollisionBounds().y - this->GetCollisionBounds().h;
				this->DeltaMove.y = 0;
			}
			isTouchingSomething = true;
			break; 
		}
	}

	if (!isTouchingSomething)
	{
		this->Grounded = false;
		this->Position.y += DeltaMove.y;
	}
};


