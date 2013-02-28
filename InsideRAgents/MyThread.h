#include"MessageEvent.h"
#include "MotionAgent.h"
#include "thread.h"
#include <iostream>


class MyThread: public thr::Thread {
public:
  //
  MyThread()  {}
  virtual void execute() {
    
  //char* sendMessageSender(m, me, a, a1);
  }
 char* sendMessageSender(Message m,MessageEvent me,MotionAgent a, MotionAgent a1){
//MotionAgent motion = MotionAgent("motion");
//MotionAgent motion1 = MotionAgent("motion1");

return (me.sendMessage(a.getAgentId(), m.getMessage(), a1.getAgentId()));
}
  //bool done() const { return __done; }
//private:
  //bool __done;
};

