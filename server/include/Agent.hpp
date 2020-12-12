#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include <memory>
#include "City.hpp"

class Agent{

        unsigned int agent_id;
        std::weak_ptr<City> origin;
        std::weak_ptr<City> destination;
        std::string sorigin;
        std::string sdestination;
        int load;

        public:
           Agent();
           Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load);
           //Agent(int _id, std::string _origin, std::string _destination, int _load);
           std::weak_ptr<City> getOrigin();
           std::weak_ptr<City> getDestination();
           int getLoad();
           int getID();
};

#endif
