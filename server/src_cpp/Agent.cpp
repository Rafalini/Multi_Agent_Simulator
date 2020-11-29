#include "Agent.hpp"
#include <iostream>

Agent::Agent(){}
Agent::Agent(City _origin, City _destination, int _load):
      origin(_origin), destination(_destination), load(_load)
      {
          std::cout << "tworzenie agenta" << std::endl;
          agent_id = id++;
      }
Agent::Agent(std::string _origin, std::string _destination, int _load):
      sorigin(_origin), sdestination(_destination), load(_load)
      {
          agent_id = id++;
      }
