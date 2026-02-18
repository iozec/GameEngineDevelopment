#include "Subscriber.h"
#include "Broker.h" 

void Subscriber::Subscribe(const std::string& topic) {
    if (broker) {
        broker->Subscribe(topic, this);
    }
}
