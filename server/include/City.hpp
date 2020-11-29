#ifndef CITY
#define CITY

#include <string>
#include <vector>

class City{

        std::string name="_";
        double ox=0;
        double oy=0;

        public:
           City();
           City(std::string _city, double _ox, double _oy);
           std::string get_name();
           double get_ox();
           double get_oy();
};

#endif
