#include "Publisher.h"
#include "Broker.h"
#include "Message.h"

void Publisher::Publish(const std::string& topic, IEventData* EventData) const
{
    Broker::INSTANCE().Publish(topic, EventData);
}
