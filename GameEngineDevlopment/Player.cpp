#include "Player.h"
#include "Input.h"

Player::Player(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent):
	Pawn(renderer, path, x, y, isTransparent),
	Publisher(broker)

{

}


void Player::Update(){

	Input::INSTANCE().Update();
	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_UP)) {
	UpdatePosition(0, -1);

	if (Input::INSTANCE().isKeyHeld(SDL_SCANCODE_P)) {
		Publish("Test", new Message("<Test message>"));
	}

}


