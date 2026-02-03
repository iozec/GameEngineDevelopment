#pragma once
class Broker
{

#include "Broker.h"
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
	class Subscriber;
	class Message;

	class Broker
	{
		std::unordered_map<std::string, std::queue<Message*>> topics;
		std::unordered_map<std::string, std::vector<Subscriber*>> subscriber;
	public:
		void Subscribe(const std::string& topic, Subscriber* sub);
		void Publish(const std::string& topic, Message message);



};

