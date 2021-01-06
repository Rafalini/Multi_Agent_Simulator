#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include <memory>

#include "City.hpp"
#include "Agent.hpp"

class Agents_Map{
        data_table table;
        std::vector<std::shared_ptr<City>>  points;
        std::vector<std::shared_ptr<Agent>> agents;

        public:
           Agents_Map();
           void add_map_point(int id, std::string name, double ox, double oy);
           void add_agent(int id, std::string origin, std::string destination, int load);
           void add_path(int begin, int end, int type);
           void run();
           std::string get_agent_route(int id);
};

#endif
