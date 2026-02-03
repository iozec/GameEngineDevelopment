#pragma once
#include "Pawn.h"
#include "Publisher.h"
class Player :

	public Pawn,
	public Publisher
{
public:

	Player(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);

	void Update() override;

};


