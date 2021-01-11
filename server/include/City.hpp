//300190
//Klasa reprezentująca miasto.

#ifndef CITY
#define CITY

#include <string>
#include <vector>
#include <memory>
#include <semaphore.h>

#include "Road.hpp"

class City;
class Road;

// Struktura opisująca połączenie między wierzchołkami grafu
// Dane miasto ma listę sąsiadów i dróg ich któe go łączą z tymi sąsiadami
struct Neighbor{
  std::shared_ptr<City> city;
  std::shared_ptr<Road> road;
  double distance;
};

class City{
        int id;
        std::string name="";
        double ox=0;
        double oy=0;
//lista sąsiadóœ
        std::vector<Neighbor> neighbors;
//kolejka do któej wspiują się agenci z identyfikatorem, czasem przyjazdu i czasem na jaki zajmą miasto
        std::vector<std::pair<int, std::pair<int, int>>> agents_queue; //arrival_time, loading time, id
//kolejka agentów, identyfikator i czas wstępu do miasta
        std::vector<std::pair<int, int>> agents_start_times; //id, start time

        sem_t queue_sem;

        public:
//przelicznik odległości na mapie na rzeczywiste jednostki
          static const int DISTANCE_PER_UNIT = 988;

           City(int _id, std::string _city, double _ox, double _oy);

           void addNeighbor(std::shared_ptr<City> Neighbor, std::shared_ptr<Road> road);
           double getDistanceTo(City city);
           double getDistanceTo(std::shared_ptr<City> city);

           void syncAddToQue(int id, int time, int loading_time);
           int  syncGetStartTime(int id);
//funkcja którą woła planista aby przydzielić agentom czasy wejścia do miasta
           void organizeTimes();

           int getId();
           std::string getName();
           double getOx();
           double getOy();
           std::vector<Neighbor> getNeighbors();
};

#endif
