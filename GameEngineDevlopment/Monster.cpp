#include "Monster.h"
#include <iostream>
#include "Message.h"

Monster::Monster(std::shared_ptr<SDL_Renderer> renderer,
	const std::string path, int x, int y, bool isTransparent) :
	Pawn(renderer, path, x, y, isTransparent)
{
}

void Monster::Receive(const IEventData* EventData, const std::string& topic)
{
	if(topic == "Test")
	{
		std::cout << "Received message: " <<
			static_cast<const Message*>(EventData)->getMessage()
			<< ", from topic: " << topic << std::endl;
	}
}
