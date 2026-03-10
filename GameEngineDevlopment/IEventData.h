#pragma once
#include <string>

class Publisher;

class IEventData
{
public:
	const Publisher& Sender;
	IEventData(const Publisher& sender) : Sender(sender) {}
};

