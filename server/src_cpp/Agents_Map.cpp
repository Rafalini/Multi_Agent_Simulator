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
#include <ctime>
#include <cstdlib>

#include "Agents_Map.hpp"
#include "City.hpp"
#include "Agent.hpp"
#include "Road.hpp"

Agents_Map::Agents_Map()
      {
        srand(time(NULL));
      }

void Agents_Map::add_map_point(int id, std::string name, double ox, double oy)
      {
          points.push_back(std::make_shared<City>(id,name,ox,oy));
      }

void Agents_Map::add_agent(int id, std::string s_origin, std::string s_destin, int load, int capacity)
      {
          auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_origin;});
          auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_destin;});

          if(origin != points.end() && destination != points.end())
                agents.push_back(std::make_shared<Agent>(id, *origin, *destination, load, capacity, limits));
      }

void Agents_Map::add_path(int begin, int end, int type)
    {
        auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_id() == begin;});
        auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_id() == end;});

        std::shared_ptr<Road> myroad = std::make_shared<Road>(type, limits);

        points[origin     -points.begin()].get()->add_neighbor(*destination, myroad);
        points[destination-points.begin()].get()->add_neighbor(*origin, myroad);
    }

void Agents_Map::add_speeds(int v1, int v2, int v3)
{
    limits.max_speed_0 = v1;
    limits.max_speed_1 = v2;
    limits.max_speed_2 = v3;
}
void Agents_Map::add_loading_speeds(int load, int unload)
{
    limits.load_time_per_unit = load;
    limits.unload_time_per_unit = unload;
}
void Agents_Map::add_accident(double n, int work_time, int break_time)
{
    limits.accident = n;
    limits.non_stop_working_time = work_time;
    limits.break_time = break_time;
}

void Agents_Map::run()
      {
            std::cout << "running simulation..." << std::endl;

            for(auto agent : agents)
                agent->agent_go();
      }

std::string Agents_Map::get_agent_route(int id)
      {
        std::string route;
        auto agent = std::find_if(agents.begin(), agents.end(), [&id](std::shared_ptr<Agent> &a)
                                                                    {return a->get_id() == id;});
        if(agent != agents.end())
            route = (*agent)->get_history();

        return route;
      }

std::string Agents_Map::get_agent_raport(int id)
      {
        std::string raport;
        auto agent = std::find_if(agents.begin(), agents.end(), [&id](std::shared_ptr<Agent> &a)
                                                                    {return a->get_id() == id;});
        if(agent != agents.end())
            raport = (*agent)->get_raport();

        return raport;
      }


void Agents_Map::clean()
      {
        points.clear();
        agents.clear();
      }

BOOST_PYTHON_MODULE(map_module)
      {

          boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
              .def("add_map_point", &Agents_Map::add_map_point)
              .def("add_agent", &Agents_Map::add_agent)
              .def("run", &Agents_Map::run)
              .def("get_agent_route", &Agents_Map::get_agent_route)
              .def("get_agent_raport", &Agents_Map::get_agent_raport)
              .def("add_path", &Agents_Map::add_path)
              .def("add_speeds", &Agents_Map::add_speeds)
              .def("add_loading_speeds", &Agents_Map::add_loading_speeds)
              .def("add_accident", &Agents_Map::add_accident)
              .def("clean", &Agents_Map::clean);
      }
