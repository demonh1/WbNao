#include "Agent.h"
#include <cstring>

Agent:: Agent(){ };
Agent::Agent(std::string s, unsigned id): name(s),aId(id)  { }


void Agent::setName(std::string _name){ _name = name; }

std::string Agent::getName() { return name; }

void Agent::setAgentId(unsigned id) {
id = aId;
}
unsigned Agent::getAgentId() { return aId; }


