#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include "City.hpp"

class Agents_Map{
        std::vector<City> cities;

        public:
           Agents_Map();
           void add_city(std::string name, double ox, double oy);
           void run();
           void idiotic_respond();
           //friend std::ostream& operator<< (std::ostream& os, Server_Core& s);
};

#endif
