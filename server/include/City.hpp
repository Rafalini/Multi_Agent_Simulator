#ifndef CITY
#define CITY

#include <string>
#include <vector>
#include <memory>

enum connections {COUNTRY=0,EXPRESS,HIGHWAY};

class City;

struct neighbor{
  double distance;
  std::shared_ptr<City> neighbor;
  connections connection;
};

class City{
        int id;
        std::string name="_";
        double ox=0;
        double oy=0;

        std::vector<neighbor> neighbors;
        //std::vector<std::pair<neighbor,road>> neighbors;

        public:
           City();
           City(int _id, std::string _city, double _ox, double _oy);

           void add_neighbor(std::shared_ptr<City> neighbor, int conn);
           double get_distance_to(City city);

           int get_id();
           std::string get_name();
           double get_ox();
           double get_oy();
           std::vector<neighbor> get_neighbors();

};

#endif
