#pragma once
#include <cstdint>
#include <string>

class IEventData;
class Publisher
{

public:

	//Publisher(Broker* b) : broker(b) {}
	Publisher() {}
	void Publish(const std::string& topic, IEventData* EventData) const;
};

	/*Publisher(Broker& broker) : broker(&broker) {}
	void Publish(const std::string& topic, Message* message) const
	{
		broker->Publish(topic, message);
	}*/

