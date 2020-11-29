#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include "City.hpp"

class Agent{

        static unsigned int id;
        unsigned int agent_id;
        City origin;
        City destination;
        std::string sorigin;
        std::string sdestination;
        int load;

        public:
           Agent();
           Agent(City _origin, City _destination, int _load);
           Agent(std::string _origin, std::string _destination, int _load);

};

#endif
