#include "Agent.hpp"
#include <iostream>
#include <memory>

Agent::Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load)
																 : agent_id(_id), origin(_origin), destination(_destination), load(_load) {}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return load;}
int Agent::getID() {return agent_id;}
