#include "Publisher.h"
#include "Broker.h"
#include "Message.h"

void Publisher::Publish(const std::string& topic, IEventData* message) const
{
    if (broker) {
        broker->Publish(topic, message);
    }
}
