#include "City.hpp"
#include "Road.hpp"

#include <math.h>
#include <memory>

City::City(){}
City::City(int _id, std::string _city, double _ox, double _oy): id(_id), name(_city), ox(_ox), oy(_oy){}
std::string City::get_name(){return name;}
double City::get_ox(){return ox;}
double City::get_oy(){return oy;}
int City::get_id(){return id;}

std::vector<neighbor>  City::get_neighbors(){return neighbors;}

void City::add_neighbor(std::shared_ptr<City> city, std::shared_ptr<Road>road)
        {
          neighbors.push_back(neighbor());
          neighbors[neighbors.size()-1].distance = get_distance_to(*city);
          neighbors[neighbors.size()-1].city = city;
          neighbors[neighbors.size()-1].road = road;
        }
double City::get_distance_to(City city) {return sqrt(pow(city.get_ox()-ox,2)+pow(city.get_oy()-oy,2));}
double City::get_distance_to(std::shared_ptr<City> city) {return sqrt(pow(city->get_ox()-ox,2)+pow(city->get_oy()-oy,2));}
