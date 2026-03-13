#pragma once
#include <string>

class IEventData;

class Subscriber
{
public:
	Subscriber() {}

	void Subscribe(const std::string& topic);

	virtual void Receive(const IEventData* message, const std::string& topic) = 0;
};

