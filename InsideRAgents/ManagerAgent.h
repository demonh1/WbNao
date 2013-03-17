#ifndef ManagerAgent_h
#define ManagerAgent_h
#include "Agent.h"
#include <cstring>
#include <vector>

class ManagerAgent: public Agent  {
//
public:
	ManagerAgent (std::string _name);
//int id;
std::string name;
void setUidAgents(unsigned ida);
void printIdAgentSenders( );
 

protected:
// массив где хранится список id agents
std::vector <unsigned> agentsId;

};
#endif
