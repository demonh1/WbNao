#include "ManagerAgent.h"
#include <iostream>

ManagerAgent::ManagerAgent(std::string _name): name(_name) {  }

void ManagerAgent::setUidAgents(unsigned ida) {

	agentsId.push_back(ida);
	
  
}
// print
void ManagerAgent::printIdAgentSenders( ) { 
 
	std:: cout <<"Id all agent senders: \n" ;
	for (std::vector<unsigned>::const_iterator it = agentsId.begin(); it != agentsId.end(); ++it) 
   std:: cout << *it << ' ' << std:: endl;
}

