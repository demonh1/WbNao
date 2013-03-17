#include "MessageEvent.h"
#include "MotionAgent.h"
#include "ManagerAgent.h"
#include <iostream>
#include <memory>
#include <cstring>
#include "MyThread.h"


//test
int main() {
	Message m = Message("hi",1);
	Message m0 =  Message("inform message",2);
        Message ms =  Message("wt",2);

	std::shared_ptr<MessageEvent>m1(new MessageEvent()); 
        MessageEvent m12 =  MessageEvent(); 
	//QueueMessage aa =  QueueMessage(0);

	//vector<Message> pq;
//pq.push_back(m);
//pq.push_back(m0);

//cout << "Size of ...\n";
 // while (!pq.empty())
 // {
 //    cout  << pq.size() << "\n";
 //    pq.pop_back();
//  }
 // cout << endl;
//std:: string str = "Sender";

m1 -> addMessageToQueue(m);
m1 -> addMessageToQueue(m0);
std::cout  << "size:"; 
 m1->sizeQueue();
//cout << "Type: " << m1 ->getTypeMessage(m1->INFORM) << "\n";
//m1 -> delMessageItemToQueue(m,0);
//cout << (msg.sendMessage(motion.getName(), m.getMessage(),ma.getName())) << "\n";
MotionAgent motion = MotionAgent("motion");
MotionAgent motion1 = MotionAgent("motion1");
m1 -> delLastItemMessage(); 
//std:: cout << "Sender id " << motion.getAgentId() << std::endl;
//std::cout << "Receiver id " << motion1.getAgentId() << std:: endl;

std:: cout << "Sender" << "\n" << m1 -> sendMessage(motion.getName(), m.getMessage(), motion1.getName()) << std:: endl;
std:: cout << "Sender id: " << motion.getAgentId() << "\n" << m1 -> sendMessage(motion.getAgentId(), m.getMessage(), motion1.getAgentId()) << std:: endl;
std:: cout  << "size:";  
 m1->sizeQueue();


MyThread thread; 
  //std::cout << "Thread: " << thread.sendMessageSender(m,m12,motion,motion1) << std::endl;
  thread.start();

////
	MotionAgent motion2 = MotionAgent("motion2");
	MotionAgent motion3 = MotionAgent("motion3");
	MyThread thread1; 
	//std::cout << "Thread: " << thread1.sendMessageSender(m0,m12,motion2,motion3) << std::endl;
	thread.start();
	thread.join();
//	std::cout << "Thread end: " << thread.sendMessageSender(m0,m12,motion2,motion3) << std::endl;
////
	ManagerAgent manager = ManagerAgent("manager");
	manager.setUidAgents(motion.getAgentId());
        manager.setUidAgents(motion2.getAgentId());
        manager.setUidAgents(motion3.getAgentId());
        manager.printIdAgentSenders( );


return 0;
}

