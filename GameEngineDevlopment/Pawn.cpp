#include "Pawn.h"
#include "Broker.h"

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, Broker& broker) {


	Sprite = std::unique_ptr<Bitmap>(
		new Bitmap(renderer, path, x, y, isTransparent));

	
}

void Pawn::UpdatePosition(int x, int y)
{
	X += x;
	Y += y;
}

void Pawn::Draw() {

	Sprite.get()->Draw(X, Y);
}

int Pawn::GetX() {

	return X;
}

void Pawn::SetX(int x) {

	X = x;
}

int Pawn::GetY() {

	return Y;
}

void Pawn::SetY(int y) {

	Y = y;
}

void Pawn::Update() {}

