#pragma once
#include <string>


class Message
{
	std::string messageText;
public:
	Message(const std::string& message) : messageText(message) {}

	std::string getMessage() const { return messageText; }
};

