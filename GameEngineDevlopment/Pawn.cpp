#include "Pawn.h"
#include "Broker.h"

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, Broker& broker) {


	Sprite = std::unique_ptr<Bitmap>(
		new Bitmap(renderer, path, x, y, isTransparent));

	Position.x = x;
	Position.y = y;


}

void Pawn::UpdatePosition(int x, int y)
{
	Position.x += x;
	Position.y += y;
}

SDL_Rect Pawn::GetCollisionBounds() const
{
	SDL_Rect r = Sprite->GetImageBounds();
	r.x = Position.x;
	r.y = Position.y;
	return r;
}


void Pawn::Draw()
{
	Sprite->Draw(Position.x, Position.y);
	this->DrawCollider(this->GetCollisionBounds());
}
void Pawn::DrawCollider(SDL_Rect Collider) const
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;

	SDL_GetRenderDrawColor(Sprite->GetRenderer().get(), &R, &G, &B, &A);

	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), 255, 255, 255, 255);

	const SDL_FRect dstRect = {
		static_cast<float>(Collider.x),
		static_cast<float>(Collider.y),
		static_cast<float>(Collider.w),
		static_cast<float>(Collider.h)
	};

	SDL_RenderRect(Sprite->GetRenderer().get(), &dstRect);

	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), R, G, B, A);
}


int Pawn::GetX() {

	return Position.x;
}

void Pawn::SetX(int x) {

	Position.x = x;
}

int Pawn::GetY() {

	return Position.x;
}

void Pawn::SetY(int y) {

	Position.y = y;
}

void Pawn::Update() {}

