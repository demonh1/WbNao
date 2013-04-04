#include "Message.h"

Message::Message () { }

Message::Message (char* _msg, long time, int _type ):msg(_msg), timeStamp(time),type(_type) { }

Message::~Message () { }


int Message::getTypeMessage (int type) { 
return (type == 1) ? MessageType::INFORM :  MessageType::QUERY;
 }

void Message::setMessage (char* _msg) { _msg = msg; }

char* Message::getMessage() const { return this -> msg; }

