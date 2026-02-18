#include "Player.h"
#include "Input.h"
#include "Message.h" 

Player::Player(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, Broker& broker) :
	Pawn(renderer, path, x, y, isTransparent, broker),
	Publisher(&broker) 
{
}

void Player::Update() {

	Input::INSTANCE().Update();


	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP)) {
		UpdatePosition(0, -1);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_DOWN)) {
		UpdatePosition(0, 1);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_LEFT)) {
		UpdatePosition(-1, 0);
	}
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_RIGHT)) {
		UpdatePosition(1, 0);
	}


	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_P)) {

		//Publish("Test", new Message(*this));
		Publish("Test", new Message(std::string("Test Message")));
	}
};


