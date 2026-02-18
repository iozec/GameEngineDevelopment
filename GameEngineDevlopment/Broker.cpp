#include "Broker.h"
#include "Subscriber.h"
#include "Message.h"


Broker* Broker::_instance = nullptr;


void Broker::Subscribe(const std::string& topic, Subscriber* sub) {
    if (sub != nullptr) {
        subscriber[topic].push_back(sub);
    }
}


void Broker::Publish(const std::string& topic, Message* message) {
    topics[topic].push(message);

   
    for (auto sub : subscriber[topic]) {
        if (sub != nullptr) {
            sub->Receive(message, topic);
        }
    }
}