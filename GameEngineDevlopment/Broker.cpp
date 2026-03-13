#include "Broker.h"
#include "Subscriber.h"
#include "Message.h"


void Broker::Subscribe(const std::string& topic, Subscriber* sub) {
    if (sub != nullptr) {
        subscriber[topic].push_back(sub);
    }
}


void Broker::Publish(const std::string& topic, IEventData* message) {
    topics[topic].push(message);

   
    for (auto sub : subscriber[topic]) {
        if (sub != nullptr) {
            sub->Receive(message, topic);
        }
    }
}


 Broker& const Broker::INSTANCE()
{
    if (!Broker::_instance)
        Broker::_instance = new Broker();

    return *Broker::_instance;
}
Broker* Broker::_instance = nullptr;