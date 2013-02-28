#ifndef MotionAgent_h
#define MotionAgent_h
#include "Agent.h"
#include <cstring> 

using namespace std;

class MotionAgent : public Agent { 
public:
	MotionAgent (string name);
string sId;
int agentId; 
//void setName(char* _name){ _name = sId;} 
//char* getName() {return sId;}
//int getAgentID() { return agentId; } 

};
#endif
