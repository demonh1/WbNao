#ifndef Agent_h
#define Agent_h
#include <string> 



class Agent {
public:
unsigned aId;
//Agent owner;
std::string name;
int source;
Agent();
Agent(std::string s, unsigned id);
 virtual ~Agent() { };

void setName(std::string _name); 
std::string getName() const;

void setAgentId(unsigned id);
unsigned getAgentId() const;

void createAgentAction();
void killAgentAction();
//Thread* t = new Thread();
//t -> start();
};
#endif
