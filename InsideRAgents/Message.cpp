#include "Message.h"

Message::Message () { }

Message::Message (char* _msg, long time ):msg(_msg), timeStamp(time), INFORM(1), QUERY(2) { }

Message::~Message () { }


int Message::getTypeMessage (int type) { 
return (type == 1) ? INFORM :  QUERY;
 }

void Message::setMessage (char* _msg) { _msg = msg; }

char* Message::getMessage() { return msg; }

