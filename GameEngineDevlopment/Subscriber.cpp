#include "Subscriber.h"
#include "Message.h"
#include "Broker.h" 

void Subscriber::Subscribe(const std::string& topic) {

	Broker::INSTANCE().Subscribe(topic,this);
}
