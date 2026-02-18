#include "Publisher.h"
#include "Broker.h"
#include "Message.h"

void Publisher::Publish(const std::string& topic, Message* message) const
{
    if (broker) {
        broker->Publish(topic, message);
    }
}
