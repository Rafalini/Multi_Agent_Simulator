#include "Agent.hpp"
#include <iostream>
#include <memory>

unsigned int Agent::id = 0;

Agent::Agent(){}
Agent::Agent(std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load) : origin(_origin), destination(_destination), load(_load) {
	std::cout << "tworzenie agenta" << std::endl;
	agent_id = ++id;
}
Agent::Agent(std::string _origin, std::string _destination, int _load) : sorigin(_origin), sdestination(_destination), load(_load) {
	agent_id = ++id;
}
