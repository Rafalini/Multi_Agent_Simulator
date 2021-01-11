#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "City.hpp"
#include <semaphore.h>
#include <thread>

class City;
struct neighbor;

struct graph_node{
  std::weak_ptr<City> city;
  std::weak_ptr<City> previous;

  graph_node(std::weak_ptr<City> _city, std::weak_ptr<City> _previous)
    : city(_city), previous(_previous) {}
  graph_node(std::weak_ptr<City> _city)
      : city(_city) {}
  graph_node(){}
};

struct data_table{
  int max_speed_0;
  int max_speed_1;
  int max_speed_2;

  double accident;

  int load_time_per_unit;
  int unload_time_per_unit;

  int non_stop_working_time;
  int break_time;
};

class Agent{
    private:
        static const int accident_rate = 100; //how longe distance has to be to accident may happen [km]
        static const int time_scale = 5; //how longe distance has to be to accident may happen [km]

        std::thread t;

        int agent_id;
        std::weak_ptr<City> origin;
        std::weak_ptr<City> destination;
        int total_load_to_transport;
        int capacity;
        int current_load=0;
        int time_on_track=0; //minutes
        int actual_time=0;   //minutes

        data_table limits;
        //statistics
        int num_of_breaks=0;
        int goods_delivered=0;
        int distance_made=0;
        int total_time_on_track=0;

        std::vector<int> path; //ids of nodes after path finding
        std::vector<std::string> history; //list of events, base of animation
        bool accident_happened = false;
        bool running = true;
        bool working_hours = true;

        std::string print_moving(int loc_id, int duration);
        std::string print_moving(int loc_id, int duration, double procent);
        std::string print_waiting(int loc_id, int duration);
        std::string print_accident(int loc_id, int duration, double procent);
        bool check_if_accident(int distance);

        sem_t acces_sem;
        sem_t break_sem;
public:

//public for tests
        void path_finder(std::shared_ptr<City> origin, std::shared_ptr<City> destination);
        void insert_first_neighbors(std::vector<std::pair<double,graph_node>> &points, std::shared_ptr<City> &origin, std::shared_ptr<City> &target, std::map<int,int> &history);
        void insert_neighbors(std::vector<std::pair<double,graph_node>> &points, double cost,	graph_node &node,	std::shared_ptr<City> &target, std::map<int,int>&history);
        void agent_load();
        void agent_unload();
        void agent_drive(std::shared_ptr<City> position, std::shared_ptr<City> target);
        void hit_the_road(int time, neighbor next_city);//jack

        std::vector<int> get_path(); //ids of nodes

        Agent(); //for tests

//public methods
        Agent(int id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, int _capacity, data_table _table);
        std::weak_ptr<City> getOrigin();
        std::weak_ptr<City> getDestination();
        int getLoad();
        int get_id();
        int get_num_of_breaks();
        int get_goods_delivered();
        int get_distance_made();
        int get_total_time_on_track();

        void agent_go();
        void agent_stop();
        void agent_travel();
        std::string get_history();
        std::string get_raport();
        std::vector<std::string> get_his(); //for tests
        void unlock_mutex();
        void acces_sched();
        bool is_running();
};

#endif
