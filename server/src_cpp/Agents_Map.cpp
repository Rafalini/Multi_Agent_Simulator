#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include "Agents_Map.hpp"
#include "City.hpp"
#include <string>
#include <boost/python.hpp>
#include <iostream>
//#include <pthread>

void initMapka() {std::cout << "init mapki" << std::endl;}


BOOST_PYTHON_MODULE(map_module)
    {
        initMapka();
        boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
            .def("idiotic_respond", &Agents_Map::idiotic_respond)
            .def("add_city", &Agents_Map::add_city);
    }

Agents_Map::Agents_Map(){}

void Agents_Map::add_city(std::string name, double ox, double oy)
      {
            //City *c = new City(name,ox,oy);
            //cities.push_back();
            std::cout << "dodaje miasto: "<<name<<" "<<ox<<" "<<oy<<std::endl;
      }

void Agents_Map::run()
      {
            std::cout << "running map..." << std::endl;
      }

void Agents_Map::idiotic_respond()
      {
            std::cout << "elunia" << std::endl;
      }
