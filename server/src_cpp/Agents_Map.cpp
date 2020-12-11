#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <string>
#include <boost/python.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "Agents_Map.hpp"
#include "City.hpp"
#include "Agent.hpp"

Agents_Map::Agents_Map(){}

void Agents_Map::add_city(std::string name, double ox, double oy)
      {
          cities.push_back(std::make_shared<City>(name,ox,oy));
      }

void Agents_Map::add_agent(std::string s_origin, std::string s_destin, int load)
      {
          auto origin =       std::find_if(cities.begin(), cities.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_origin;});
          auto destination =  std::find_if(cities.begin(), cities.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_destin;});
          if(origin != cities.end() && destination != cities.end())
                std::cout << "ok " << origin->get()->get_name() << " "<< destination->get()->get_name() << std::endl;
              //agents.push_back(Agent(*origin, *destination, load));
          std::cout << "eluwa" << std::endl;

      }

void Agents_Map::run()
      {
            std::cout << "running map..." << std::endl;
      }

std::string Agents_Map::get_agent_route(int id)
      {
        std::string output = "output string id: ";
        output += id;
        return output;
      }


BOOST_PYTHON_MODULE(map_module)
    {

        boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
            .def("add_city", &Agents_Map::add_city)
            .def("add_agent", &Agents_Map::add_agent)
            .def("run", &Agents_Map::run)
            .def("get_agent_route", &Agents_Map::get_agent_route);
    }
