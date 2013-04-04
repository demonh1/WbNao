#include "MessageEvent.h"
#include "Message.h"
#include <iostream>



template <typename T>
std::string MessageEvent::toString (const T &t) {
    std::ostringstream os;
    os << t;
    return os.str();
}


template <typename T>
T MessageEvent::fromString (const std::string &str) {
   std::istringstream is(str);
    T t;
    is >> t;
    return t;
}
//MessageEvent::MessageEvent ( ) { }
//MessageEvent::~MessageEvent () { }

char* MessageEvent::sendMessage(unsigned idSender, Message msg, unsigned idReceiver) { 
addMessageToQueue(msg); 
return msg.getMessage();
 }

char* MessageEvent::sendMessage(std::string nameSender, Message msg, std::string nameReceiver) {
addMessageToQueue(msg); 
return msg.getMessage();
 }

void MessageEvent::addMessageToQueue(Message msg) {

pq.push_back(msg);
} 

void MessageEvent::delMessageItemToQueue(Message msg, int index) {
pq.erase(pq.begin()+index);
}

void MessageEvent::sizeQueue() {
std::cout <<  pq.size() << std::endl; 
}
//void sizeQueue() { pq.size();}
void MessageEvent::delLastItemMessage() {
pq.pop_back();
}


