//300190
//Klasa opakowująca agentów i mapę razem. Zapewnia funkcjonalności odczytu i zapisu danych.

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <string>
#include <boost/python.hpp>
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

void Agents_Map::addMapPoint(int id, std::string name, double ox, double oy){
          points.push_back(std::make_shared<City>(id,name,ox,oy));
      }

void Agents_Map::addAgent(int id, std::string s_origin, std::string s_destin, int load, int capacity){
        auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->getName() == s_origin;});
        auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->getName() == s_destin;});

        if(origin != points.end() && destination != points.end()){
          agents_backup.push_back(std::make_shared<Agent>(id, *origin, *destination, load, capacity, limits));
          std::vector<int> v{id,0,0,0,0};
          stats.push_back(v);
        }
      }

void Agents_Map::addPath(int id, int begin, int end, int type){
        auto origin =       std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->getId() == begin;});
        auto destination =  std::find_if(points.begin(), points.end(), [&](std::shared_ptr<City> obj){return obj.get()->getId() == end;});

        roads.push_back(std::make_shared<Road>(id, type, limits));

        points[origin     -points.begin()].get()->addNeighbor(*destination, roads[roads.size()-1]);
        points[destination-points.begin()].get()->addNeighbor(*origin, roads[roads.size()-1]);
    }

void Agents_Map::addSpeeds(int v1, int v2, int v3){
        limits.max_speed_0 = v1;
        limits.max_speed_1 = v2;
        limits.max_speed_2 = v3;
    }
void Agents_Map::addLoadingSpeeds(int load, int unload){
        limits.load_time_per_unit = load;
        limits.unload_time_per_unit = unload;
    }
void Agents_Map::addAccident(double n, int work_time, int break_time){
        limits.accident = n;
        limits.non_stop_working_time = work_time;
        limits.break_time = break_time;
    }

void Agents_Map::run(){
        agents = agents_backup;
        std::vector<std::thread> running;

        std::thread sched(&Agents_Map::scheduler, this);

        for(auto agent : agents)
            agent->agentGo();

        for(auto agent : agents)
            agent->agentStop();

       sched.join();
    }

void Agents_Map::scheduler(){
        long unsigned int finished_agents=0;
        while(true){
          finished_agents=0;
          for(auto agent : agents) //acquire all tickets = all agents waiting
            if(agent->isRunning() == true)
              agent->accesSched(); //it will wait for working Agenst, and acces instantly for finished Agents

          for(auto city : points)
            city->organizeTimes(); //organize cities

          for(auto agent : agents){ //acquire all tickets = all agents waiting
            if(agent->isRunning() == false)
              finished_agents++;
            agent->unlockMutex();
          }

          if(finished_agents == agents.size())
            break;
        }
      }


std::string Agents_Map::getAgentRoute(int id){
        std::string route;
        auto agent = std::find_if(agents.begin(), agents.end(), [&id](std::shared_ptr<Agent> &a)
                                                                    {return a->getId() == id;});
        if(agent != agents.end())
            route = (*agent)->getHistory();

        return route;
      }

std::string Agents_Map::getAgentRaport(int id){
        std::string raport;
        auto agent = std::find_if(agents.begin(), agents.end(), [&id](std::shared_ptr<Agent> &a)
                                                                    {return a->getId() == id;});
        if(agent != agents.end())
          raport = (*agent)->getRaport();

        return raport;
      }

void Agents_Map::clean() {
        points.clear();
        agents.clear();
      }

std::string Agents_Map::getAgentStats(int id, int runs){
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

void Agents_Map::restart(){
        for(long unsigned int i=0; i<agents.size(); ++i){
              stats[i][1] += agents[i]->getGoodsDelivered();
              stats[i][2] += agents[i]->getTotalTimeOnTrack();
              stats[i][3] += agents[i]->getDistanceMade();
              stats[i][4] += agents[i]->getNumOfBreaks();
        }
        //for(auto road : roads)
            //road->randomTimes();
      }

std::string Agents_Map::getPaths(){
        std::string output=" ";

        sort(roads.begin(), roads.end(), []
        (const std::shared_ptr<Road>&r1, const std::shared_ptr<Road>&r2)
                      {return r1->getBeginTime() < r2->getBeginTime();});

        for(auto path : roads)
          if(path->getEndTime()!=0)
            output += std::string("{\"path_id\": \"")+
                      std::to_string(path->getId())+
                      std::string("\", \"trafic_efficiency\" : \"")+
                      std::to_string(path->getInTraficEfficiency())+
                      std::string("\", \"begin_time\" : \"")+
                      std::to_string(path->getBeginTime())+
                      std::string("\", \"end_time\" : \"")+
                      std::to_string(path->getEndTime())+
                      std::string("\" } ,");

        output = output.substr(0, output.size()-2);
        return output;
      }


BOOST_PYTHON_MODULE(map_module){
          boost::python::class_<Agents_Map>("Agents_Map", boost::python::init<>())
              .def("addMapPoint", &Agents_Map::addMapPoint)
              .def("addAgent", &Agents_Map::addAgent)
              .def("run", &Agents_Map::run)
              .def("restart", &Agents_Map::restart)
              .def("getAgentRoute", &Agents_Map::getAgentRoute)
              .def("getAgentRaport", &Agents_Map::getAgentRaport)
              .def("getAgentStats", &Agents_Map::getAgentStats)
              .def("getPaths", &Agents_Map::getPaths)
              .def("addPath", &Agents_Map::addPath)
              .def("addSpeeds", &Agents_Map::addSpeeds)
              .def("addLoadingSpeeds", &Agents_Map::addLoadingSpeeds)
              .def("addAccident", &Agents_Map::addAccident)
              .def("clean", &Agents_Map::clean);
      }
