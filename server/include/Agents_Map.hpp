#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include "City.hpp"
#include "Agent.hpp"

class Agents_Map{
        std::vector<City>  cities;
        std::vector<Agent> agents;

        public:
           Agents_Map();
           void add_city(std::string name, double ox, double oy);
           void add_agent(std::string origin, std::string destination, int load);
           void run();
           //friend std::ostream& operator<< (std::ostream& os, Server_Core& s);
};

#endif
