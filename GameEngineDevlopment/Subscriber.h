#pragma once
#include "Broker.h"
#include "Message.h"



class Subscriber
{
	Broker* broker;
public:
	Subscriber(Broker& broker) : broker(&broker) {}

	void Subscribe(const std::string& topic);

	virtual void Receive(const IEventData* message, const std::string& topic) = 0;
};

