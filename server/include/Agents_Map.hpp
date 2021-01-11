#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include <memory>
#include <semaphore.h>

#include "City.hpp"
#include "Agent.hpp"

class Agents_Map{
        data_table limits;
        std::vector<std::shared_ptr<City>>  points;
        std::vector<std::shared_ptr<Agent>> agents;
        std::vector<std::shared_ptr<Agent>> agents_backup;

        std::vector<std::vector<int>> stats;

        public:
           Agents_Map();
           void scheduler();
           void add_map_point(int id, std::string name, double ox, double oy);
           void add_agent(int id, std::string origin, std::string destination, int load, int capacity);
           void add_path(int begin, int end, int type);
           void add_speeds(int v1, int v2, int v3);
           void add_loading_speeds(int load, int unload);
           void add_accident(double n, int work_time, int break_time);
           void run();
           void restart();
           void clean();
           std::string get_agent_route(int id);
           std::string get_agent_raport(int id);
           std::string get_agent_stats(int id, int runs);
};

#endif
