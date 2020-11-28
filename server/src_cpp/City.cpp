#include "City.hpp"

City::City(){}
City::City(std::string city, double ox, double oy)
  {
      this.name = city;
      this.ox = ox;
      this.oy = oy;
  }
std::string City::get_name(){return nam;}
double City::get_ox(){return ox;}
double City::get_oy(){return oy;}
