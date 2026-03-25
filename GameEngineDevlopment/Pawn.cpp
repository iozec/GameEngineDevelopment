#include "Pawn.h"
#include "Broker.h"
#include "MouseEventData.h"
#include <iostream>
#include "imgui.h"
#include "EditorGui.h"
#include "Hierarchy.h"

int Pawn::CurrentID = 0;

Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent) {
	Sprite = std::make_unique<Bitmap>(renderer, path, x, y, isTransparent);

	filePath = path;

	Position = { x, y };
	ID = CurrentID++;

	Broker::INSTANCE().Subscribe("MouseButtonUpdate", this);
	Broker::INSTANCE().Subscribe("MousePositionUpdate", this);
}

void Pawn::Receive(const IEventData* EventData, const std::string& topic)
{
	const MouseEventData* mouseEventData = static_cast<const MouseEventData*>(EventData);

	if (topic == "MousePositionUpdate")
	{
		if (isDragging) // We only move if the left button was pressed over us
		{
			Position.x = mouseEventData->mousePositon.x - dragOffset.x;
			Position.y = mouseEventData->mousePositon.y - dragOffset.y;
		}
	}

	if (topic == "MouseWheelUpdate")
	{
	}

	if (topic == "MouseButtonUpdate")
	{
		SDL_Point mousePosition
		{
			mouseEventData->mousePositon.x,
			mouseEventData->mousePositon.y
		};

		SDL_Rect ImageBounds = GetCollisionBounds();

		if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT &&
			SDL_PointInRect(&mousePosition, &ImageBounds) &&
			mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			isDragging = true;

			// Calculate where inside the sprite we clicked
			dragOffset.x = mousePosition.x - Position.x;
			dragOffset.y = mousePosition.y - Position.y;

			std::cout << "< clicked on image" << std::endl;
			EditorGui::INSTANCE().AttachChildWindow(this);
		}

		// 3. Stop Dragging (Button Up)
		if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT &&
			mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_UP)
		{
			isDragging = false;
		}
	}
}
bool Pawn::IsOverlapping(const Pawn& Other, const SDL_Point& Delta)
{
	bool isColliding = false;

	SDL_Rect a = GetCollisionBounds();
	SDL_Rect b = Other.GetCollisionBounds();

	a.y += Delta.y;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.y > 0)      // Falling down
			a.y = b.y - a.h;  // Snap to TOP of platform
		else if (Delta.y < 0) // Jumping up
			a.y = b.y + b.h;  // Snap to BOTTOM of platform

		isColliding = true;
	}

	a.x += Delta.x;
	if (SDL_HasRectIntersection(&a, &b))
	{
		if (Delta.x > 0)      // Moving Right
			a.x = b.x - a.w;  // Snap to LEFT side of wall
		else if (Delta.x < 0) // Moving Left
			a.x = b.x + b.w;  // Snap to RIGHT side of wall

		isColliding = true;
	}

	Position.x = a.x;
	Position.y = a.y;

	return isColliding;
}


void Pawn::DrawWindow()
{
	ImGui::Begin((std::string("Pawn Window") + std::to_string(ID)).c_str());

	if (ImGui::Button("Close"))
	{
		EditorGui::INSTANCE().RemoveChildWindow(dynamic_cast<IGuiWindow*>(this));
	}

	int pos[2] = { Position.x, Position.y };
	ImGui::InputInt2("Position", pos);
	Position.x = pos[0];
	Position.y = pos[1];

	ImGui::InputInt("Speed", &speed);
	ImGui::InputInt("Gravity", &gravity);
	ImGui::InputInt("Max Fall Speed", &maxFallSpeed);

	ImGui::End();
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
	if (m_IsActive)
	{
		Sprite->Draw(Position.x, Position.y);
		this->DrawCollider(this->GetCollisionBounds());
	}
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

