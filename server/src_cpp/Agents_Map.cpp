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

Agents_Map::Agents_Map()
      {
        table.max_speed_0   = 50;
        table.max_speed_1   = 50;
        table.max_speed_2   = 50;
        table.accident      = 0.1;
        table.step          = 0.00001;
        table.load_speed    = 1;
        table.unload_speed  = 1;
      }

void Agents_Map::add_map_point(int id, std::string name, double ox, double oy)
      {
          points.push_back(std::make_shared<City>(id,name,ox,oy));
      }

void Agents_Map::add_agent(std::string s_origin, std::string s_destin, int load)
      {
          auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_origin;});
          auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_destin;});

          std::cout << typeid(*origin).name() << std::endl;

          if(origin != points.end() && destination != points.end())
                agents.push_back(std::make_shared<Agent>(*origin, *destination, load, table));
      }

void Agents_Map::add_path(int begin, int end, int type)
    {
        auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_id() == begin;});
        auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_id() == end;});

        points[origin     -points.begin()].get()->add_neighbor(*destination, type);
        points[destination-points.begin()].get()->add_neighbor(*origin, type);
    }

void Agents_Map::run()
      {
            std::cout << "running map..." << std::endl;\
            std::cout << "points: " << points.size() << std::endl;
            std::cout << "agents: " << agents.size() << std::endl;

            for(auto agent : agents)
                agent->agent_go();
      }

std::string Agents_Map::get_agent_route(int id)
      {
        for(auto agent : agents)
          if(agent->get_id() == id)
          {
            std::string route = "jade przez A, do B, do C z predkoscia swiatla "+std::to_string(id);
            //print route
            return route;
          }
        return nullptr;
      }


BOOST_PYTHON_MODULE(map_module)
    {

        boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
            .def("add_map_point", &Agents_Map::add_map_point)
            .def("add_agent", &Agents_Map::add_agent)
            .def("run", &Agents_Map::run)
            .def("get_agent_route", &Agents_Map::get_agent_route)
            .def("add_path", &Agents_Map::add_path);
    }
