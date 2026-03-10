#include "Pawn.h"
#include "Broker.h"

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent, Broker& broker) {


	Sprite = std::unique_ptr<Bitmap>(
		new Bitmap(renderer, path, x, y, isTransparent));

	Position.x = x;
	Position.y = y;


}

void Pawn::SetDeltaMove(int x, int y)
{
	DeltaMove.x = x;
	DeltaMove.y = y;
}

bool Pawn::IsOverlapping(const Pawn& Other, const SDL_Point& Delta)
{
	bool isColliding = false;

	SDL_Rect a = Sprite->GetImageBounds();
	a.x = Position.x;
	a.y = Position.y;
	SDL_Rect b = Other.Sprite->GetImageBounds();

	// move X
	a.x += Delta.x;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.x > 0) a.x = b.x - a.w;        // right
		else if (Delta.x < 0) a.x = b.x + b.w;   // left

		isColliding = true;
	}

	// move Y
	a.y += Delta.y;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.y > 0) a.y = b.y - a.h;        // down
		else if (Delta.y < 0) a.y = b.y + b.h;   // up

		isColliding = true;
	}

	Position.x = a.x;
	Position.y = a.y;

	return isColliding;
}


void Pawn::UpdatePosition(int x, int y)
{
	DeltaMove.x += x;
	DeltaMove.y += y;
	/*Position.x += x;
	Position.y += y;*/
}

SDL_Rect Pawn::GetCollisionBounds() const
{
	SDL_Rect i = Sprite->GetImageBounds();
	i.x = Position.x;
	i.y = Position.y;
	return i;
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

