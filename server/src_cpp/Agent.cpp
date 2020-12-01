#include "Agent.hpp"
#include <iostream>
#include <memory>

unsigned int Agent::id = 0;

Agent::Agent(){}
Agent::Agent(std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load)
																 : origin(_origin), destination(_destination), load(_load) {
	agent_id = ++id;
}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return load;}
