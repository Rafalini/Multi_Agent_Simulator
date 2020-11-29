#include "City.hpp"

City::City(){}
City::City(std::string _city, double _ox, double _oy): name(_city), ox(_ox), oy(_oy){}
std::string City::get_name(){return name;}
double City::get_ox(){return ox;}
double City::get_oy(){return oy;}
