#include "City.hpp"
#include "Road.hpp"

#include <math.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <semaphore.h>

City::City(){}
City::City(int _id, std::string _city, double _ox, double _oy): id(_id), name(_city), ox(_ox), oy(_oy)
{
  sem_init(&queue_sem,0,1);
}
std::string City::get_name(){return name;}
double City::get_ox(){return ox;}
double City::get_oy(){return oy;}
int City::get_id(){return id;}

std::vector<neighbor>  City::get_neighbors(){return neighbors;}

void City::add_neighbor(std::shared_ptr<City> city, std::shared_ptr<Road>road)
        {
          neighbors.push_back(neighbor());
          neighbors[neighbors.size()-1].distance = get_distance_to(*city);
          neighbors[neighbors.size()-1].city = city;
          neighbors[neighbors.size()-1].road = road;
        }
double City::get_distance_to(City city) {return sqrt(pow(city.get_ox()-ox,2)+pow(city.get_oy()-oy,2));}
double City::get_distance_to(std::shared_ptr<City> city) {return sqrt(pow(city->get_ox()-ox,2)+pow(city->get_oy()-oy,2));}

void City::sync_add_to_que(int id, int time, int loading_time)
{
    sem_wait(&queue_sem);
    agents_queue.push_back(std::make_pair(time, std::make_pair(loading_time, id)));
    sem_post(&queue_sem);
}
void City::organize_times()
{
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

int City::sync_get_start_time(int id)
{
    sem_wait(&queue_sem);
    auto iter = std::find_if(agents_start_times.begin(), agents_start_times.end(), [&id](const std::pair<int, int>&p) {return p.first==id;});
    sem_post(&queue_sem);

    if(iter != agents_start_times.end())
      return iter->second;
    return -1;
}
