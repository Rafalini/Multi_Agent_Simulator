#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "City.hpp"

struct data_table{
  int max_speed_0=1;
  int max_speed_1=2;
  int max_speed_2=3;

  int accident=1; //<0-100>

  int load_time_per_unit=5;
  int unload_time_per_unit=5;
  int load_limit=20;

  int non_stop_working_time=4;
  int break_time=1;
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
        static const int accident_rate = 100; //how longe distance has to be to accident may happen [km]
        static const int time_scale = 5; //how longe distance has to be to accident may happen [km]

        int agent_id;
        std::weak_ptr<City> origin;
        std::weak_ptr<City> destination;
        int total_load_to_transport;
        int current_load=0;

        data_table limits;
        int goods_delivered=0;
        double distance_made=0;
        int time_on_track=0;
        int progres_between_cities=0; //<0-100>%

        std::vector<int> path; //ids of nodes

        std::vector<std::string> history;
        bool accident_happened = false;


        std::string print_moving(int loc_id, int duration);
        std::string print_accident(int loc_id, int duration, double proc);

        bool check_if_accident(int distance);

public:
//public for tests
        void path_finder(std::shared_ptr<City> origin, std::shared_ptr<City> destination);
        void insert_first_neighbors(std::vector<std::pair<double,graph_node>> &points, std::shared_ptr<City> &origin, std::shared_ptr<City> &target, std::map<int,int> &history);
        void insert_neighbors(std::vector<std::pair<double,graph_node>> &points, double cost,	graph_node &node,	std::shared_ptr<City> &target, std::map<int,int>&history);
        void agent_load();
        void agent_unload();
        void agent_drive(std::shared_ptr<City> position, std::shared_ptr<City> target);
        void move_step_ahead();
        std::vector<int> get_path(); //ids of nodes

        Agent(); //for tests

//public methods
         Agent(int id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, data_table _table);
         std::weak_ptr<City> getOrigin();
         std::weak_ptr<City> getDestination();
         int getLoad();
         int get_id();
         void agent_go();
         std::string get_history();
         std::string get_raport();
         std::vector<std::string> get_his(); //for tests
};

#endif
