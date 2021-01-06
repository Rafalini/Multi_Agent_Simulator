#ifndef CITY
#define CITY

#include <string>
#include <vector>
#include <memory>
#include "Road.hpp"

class City;

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

        public:
           City();
           City(int _id, std::string _city, double _ox, double _oy);

           void add_neighbor(std::shared_ptr<City> neighbor, std::shared_ptr<Road> road);
           double get_distance_to(City city);

           int get_id();
           std::string get_name();
           double get_ox();
           double get_oy();
           std::vector<neighbor> get_neighbors();
};

#endif
