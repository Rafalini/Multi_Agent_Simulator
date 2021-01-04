#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "City.hpp"

struct data_table{
  int max_speed_0;
  int max_speed_1;
  int max_speed_2;

  double accident; //<0-1>
  double step;

  int load_speed;
  int unload_speed;
};

struct graph_node{
  std::weak_ptr<City> city;
  std::weak_ptr<City> previous;

  graph_node(std::weak_ptr<City> _city, std::weak_ptr<City> _previous)
    : city(_city), previous(_previous) {}
  graph_node(std::weak_ptr<City> _city)
      : city(_city) {}
  graph_node(){}
};

class Agent{
    private:
        data_table limits;

        unsigned int agent_id;
        std::weak_ptr<City> origin;
        std::weak_ptr<City> destination;
        int total_load_to_transport;

        std::weak_ptr<City> positionA;
        float A_B_progress;
        std::weak_ptr<City> positionB;
        std::vector<int> path; //ids of nodes
public:
//public for tests
        void path_finder(std::shared_ptr<City> origin, std::shared_ptr<City> destination);
        void insert_first_neighbors(std::vector<std::pair<double,graph_node>> &points, std::shared_ptr<City> &origin, std::shared_ptr<City> &destination);
        void insert_neighbors(std::vector<std::pair<double,graph_node>> &points, double cost,	graph_node &node,	std::shared_ptr<City> &target, std::map<int,int>history);
        void agent_transport();
        void agent_load();
        void agent_unload();
        void agent_return();
        Agent(); //for tests

//public methods
           Agent(std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, data_table _table);
           std::weak_ptr<City> getOrigin();
           std::weak_ptr<City> getDestination();
           int getLoad();
           int get_id();
           void agent_go();
};

#endif
