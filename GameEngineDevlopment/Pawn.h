#pragma once
#include "Bitmap.h"
class Pawn
{
protected:
	std::unique_ptr<Bitmap> Sprite;


	int X;
	int Y;

public:




	// Constructor
	Pawn(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent)
	{
		Sprite = std::unique_ptr<Bitmap>(
			new Bitmap(renderer, path, x, y, isTransparent));

		void Draw();

		int GetX();
		void Setx(int x);
		int GetY();
		void SetY(int y);
	}

	

};



