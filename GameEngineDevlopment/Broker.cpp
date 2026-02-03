#include "Broker.h"
#include "Subscriber.h"
class Subscriber;
class Message;

class Broker
{
	std::Subscribe(const std::string& topic, Subscriber* sub) {
		subscriber[topic].push_back(sub);
	}

	void Broker::Publish(const std::string& topic, Message* message) {
		topics[topic].push(message);
		for (const auto& sub : Subscriber* const& : subscribers[topic]) {
			sub->Receive(message, topic);
		}
	}
};