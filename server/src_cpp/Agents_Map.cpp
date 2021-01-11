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
#include <thread>

#include "Agents_Map.hpp"
#include "City.hpp"
#include "Agent.hpp"
#include "Road.hpp"

Agents_Map::Agents_Map()  {srand(time(NULL));}

void Agents_Map::add_map_point(int id, std::string name, double ox, double oy)
      {
          points.push_back(std::make_shared<City>(id,name,ox,oy));
      }

void Agents_Map::add_agent(int id, std::string s_origin, std::string s_destin, int load, int capacity)
      {
          auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_origin;});
          auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->get_name() == s_destin;});

          if(origin != points.end() && destination != points.end()){
                agents.push_back(std::make_shared<Agent>(id, *origin, *destination, load, capacity, limits));
                agents_backup.push_back(std::make_shared<Agent>(id, *origin, *destination, load, capacity, limits));
          }
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
            std::vector<std::thread> running;

            std::thread sched(&Agents_Map::scheduler, this);

            for(auto agent : agents)
                agent->agent_go();

            for(auto agent : agents)
            {
                  agent->agent_stop();
                  std::vector<int> v;
                  v.push_back(agent->get_goods_delivered());
                  v.push_back(agent->get_total_time_on_track());
                  v.push_back(agent->get_distance_made());
                  v.push_back(agent->get_num_of_breaks());
                  stats.push_back(v);
            }

           sched.join();
      }

void Agents_Map::scheduler()
{
  long unsigned int finished_agents=0;
  while(true)
  {
    finished_agents=0;
    for(auto agent : agents) //acquire all tickets = all agents waiting
        agent->acces_sched(); //it will wait for working Agenst, and acces instantly for finished Agents

    for(auto city : points)
        city->organize_times(); //organize cities

    for(auto agent : agents) //acquire all tickets = all agents waiting
    {
        if(agent->is_running() == false)
          finished_agents++;
        agent->unlock_mutex();
    }

    if(finished_agents == agents.size())
      break;
  }
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

std::string Agents_Map::get_agent_stats(int id, int runs)
{
  std::string output;

  auto stat_set = std::find_if(stats.begin(), stats.end(), [&id](std::vector<int> &v)
                                                              {return v[0] == id;});
  if(stat_set != stats.end())
    output =  std::string("{\"avg_delivered\": \"")+
              std::to_string((*stat_set)[1] / runs)+
              std::string("\", \"avg_working_time\": \"")+
              std::to_string((*stat_set)[2] / runs)+
              std::string("\", \"avg_distance\" : \"")+
              std::to_string((*stat_set)[3] / runs)+
              std::string(" km.\"}");
  return output;
}

void Agents_Map::restart()
{
  if(stats.size() == 0)
    for(auto agent : agents)
    {
          std::vector<int> v;
          v.push_back(agent->get_id());
          v.push_back(agent->get_goods_delivered());
          v.push_back(agent->get_total_time_on_track());
          v.push_back(agent->get_distance_made());
          v.push_back(agent->get_num_of_breaks());
          stats.push_back(v);
    }
  else
    for(long unsigned int i=0; i<agents.size(); ++i)
    {
          stats[i][1] += agents[i]->get_goods_delivered();
          stats[i][2] += agents[i]->get_total_time_on_track();
          stats[i][3] += agents[i]->get_distance_made();
          stats[i][4] += agents[i]->get_num_of_breaks();
    }
  agents = agents_backup;
}


BOOST_PYTHON_MODULE(map_module)
      {

          boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
              .def("add_map_point", &Agents_Map::add_map_point)
              .def("add_agent", &Agents_Map::add_agent)
              .def("run", &Agents_Map::run)
              .def("restart", &Agents_Map::restart)
              .def("get_agent_route", &Agents_Map::get_agent_route)
              .def("get_agent_raport", &Agents_Map::get_agent_raport)
              .def("get_agent_stats", &Agents_Map::get_agent_stats)
              .def("add_path", &Agents_Map::add_path)
              .def("add_speeds", &Agents_Map::add_speeds)
              .def("add_loading_speeds", &Agents_Map::add_loading_speeds)
              .def("add_accident", &Agents_Map::add_accident)
              .def("clean", &Agents_Map::clean);
      }
