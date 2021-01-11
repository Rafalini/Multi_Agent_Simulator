//300190
//Klasa reprezentująca miasto.

#include <math.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <semaphore.h>

#include "City.hpp"
#include "Road.hpp"

City::City(int _id, std::string _city, double _ox, double _oy): id(_id), name(_city), ox(_ox), oy(_oy)
{   sem_init(&queue_sem,0,1); }

std::string City::getName()                  {return name;}
double City::getOx()                         {return ox;}
double City::getOy()                         {return oy;}
int City::getId()                            {return id;}
std::vector<Neighbor>  City::getNeighbors()  {return neighbors;}

void City::addNeighbor(std::shared_ptr<City> city, std::shared_ptr<Road>road){
          neighbors.push_back(Neighbor());
          neighbors[neighbors.size()-1].distance = getDistanceTo(*city);
          neighbors[neighbors.size()-1].city = city;
          neighbors[neighbors.size()-1].road = road;
        }

double City::getDistanceTo(City city)                   {return sqrt(pow(city.getOx()-ox,2)+pow(city.getOy()-oy,2));}
double City::getDistanceTo(std::shared_ptr<City> city)  {return sqrt(pow(city->getOx()-ox,2)+pow(city->getOy()-oy,2));}

void City::syncAddToQue(int id, int time, int loading_time){
          sem_wait(&queue_sem);
          agents_queue.push_back(std::make_pair(time, std::make_pair(loading_time, id)));
          sem_post(&queue_sem);
      }

void City::organizeTimes(){
          if(agents_queue.size()>0){
            sort(agents_queue.begin(), agents_queue.end(), []
            (const std::pair<int, std::pair<int, int>>&t1, const std::pair<int, std::pair<int, int>>&t2)
            { return t1.first > t2.first; }); //sort by arrival_time

            agents_start_times.clear();            //id, start time
            agents_start_times.push_back(std::make_pair(agents_queue[0].second.second, agents_queue[0].first));
            for(unsigned long int i=1; i<agents_queue.size(); i++)                   //id,  previous_arrival_time + its_load/unload_time
                agents_start_times.push_back(std::make_pair(agents_queue[i].second.second, agents_queue[i-1].first+agents_queue[i-1].second.first));
        }
      }

int City::syncGetStartTime(int id){
          sem_wait(&queue_sem);
          auto iter = std::find_if(agents_start_times.begin(), agents_start_times.end(), [&id](const std::pair<int, int>&p) {return p.first==id;});
          sem_post(&queue_sem);

          if(iter != agents_start_times.end())
            return iter->second;
          return -1;
      }
