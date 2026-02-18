#pragma once

#include <cstdint>
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

		static Broker* _instance;

	public:

		static Broker* Instance() {
			if (_instance == nullptr) {
				_instance = new Broker();
			}
			return _instance;
		}

		void Subscribe(const std::string& topic, Subscriber* sub);
		void Publish(const std::string& topic, Message* message);



};

