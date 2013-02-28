#ifndef MessageEvent_h
#define MessageEvent_h
#include <cstdio>
#include <vector>
#include <string> 
#include <sstream>
#include "Message.h"

class MessageEvent: public Message  {
public:
	//status
	 int RECD,SENT;  // sent/received
	 std::vector<Message> pq;

	 MessageEvent () { };
	 ~ MessageEvent(){ };
         

// methods
char* sendMessage(unsigned idSender, char* msg, unsigned idReceiver);
char* sendMessage(std::string nameSender, char* msg, std::string nameReceiver);
//int isStatusMessage (int indexMessageToQueue); // RECD/SENT

// convert to string
template <typename T>
std::string toString (const T &t);

template <typename T>
T fromString (const std::string &str);

// TODO methods for working with a queue

void addMessageToQueue(Message msg);
void delMessageItemToQueue(Message msg, int index);
void sizeQueue();
void delLastItemMessage();


};
#endif
