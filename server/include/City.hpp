#ifndef CITY
#define CITY

#include <string>
#include <vector>
#include <memory>
#include <semaphore.h>

#include "Road.hpp"

class City;
class Road;

struct neighbor{
  std::shared_ptr<City> city;
  std::shared_ptr<Road> road;
  double distance;
};

class City{
        int id;
        std::string name="_";
        double ox=0;
        double oy=0;

        std::vector<neighbor> neighbors;
        std::vector<std::pair<int, std::pair<int, int>>> agents_queue; //arrival_time, loading time, id
        std::vector<std::pair<int, int>> agents_start_times; //id, start time

        sem_t queue_sem;

        public:
          static const int distance_per_unit = 988;

           City();
           City(int _id, std::string _city, double _ox, double _oy);

           void add_neighbor(std::shared_ptr<City> neighbor, std::shared_ptr<Road> road);
           double get_distance_to(City city);
           double get_distance_to(std::shared_ptr<City> city);

           void sync_add_to_que(int id, int time, int loading_time);
           int  sync_get_start_time(int id);
           void organize_times();

           int get_id();
           std::string get_name();
           double get_ox();
           double get_oy();
           std::vector<neighbor> get_neighbors();
};

#endif
