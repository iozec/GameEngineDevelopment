#pragma once
#include "Pawn.h"
#include "Subscriber.h"
class Monster : public Pawn// public Publisher
{
public:

	float baseX = 0.0f;
	float x = 0.0f;
	float speed = 0.1f;
	float range = 2.0f;
	bool movingRight = true;

	Monster(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);

	//write code for movement

	void Update() override;
};

