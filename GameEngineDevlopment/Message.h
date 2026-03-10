#pragma once
#include "IEventData.h" 
#include "Publisher.h"
class Message :
	public IEventData
{
	std::string message;
public:
	Message(const Publisher& sender, std::string message) 
		:IEventData(sender), message(message) {}
	std::string getMessage() const { return message; }
};


