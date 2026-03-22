#pragma once
#include "Pawn.h"
#include "Publisher.h"
#include <iostream>
#include "Subscriber.h"

class Broker;

class Player : public Pawn//, public Publisher
{
public:

	int health = 100;
	void takeDamage(int damage) {
		health -= damage;
		std::cout << "[C++]Player took " << damage << " damage, health now " << health << "\n";
	}

	Player(std::shared_ptr<SDL_Renderer> renderer,
		const std::string path, int x, int y, bool isTransparent);
	
	void Update() override;

	bool hasKey = false;

};


