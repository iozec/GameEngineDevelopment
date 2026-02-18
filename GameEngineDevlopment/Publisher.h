#pragma once
#include <cstdint>
#include <string>

class Broker;
class Message;


class Publisher
{
	Broker* broker;
public:

	Publisher(Broker* b) : broker(b) {}

	void Publish(const std::string& topic, Message* message) const;
};

	/*Publisher(Broker& broker) : broker(&broker) {}
	void Publish(const std::string& topic, Message* message) const
	{
		broker->Publish(topic, message);
	}*/

