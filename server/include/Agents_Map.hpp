//300190
//Klasa opakowująca agentów i mapę razem

#ifndef MAP
#define MAP

#include <string>
#include <vector>
#include <memory>
#include <semaphore.h>

#include "City.hpp"
#include "Agent.hpp"

class Agents_Map{
        Data_table limits;
        std::vector<std::shared_ptr<City>>  points;
        std::vector<std::shared_ptr<Agent>> agents;
        std::vector<std::shared_ptr<Road>>  roads;
        std::vector<std::shared_ptr<Agent>> agents_backup;

        std::vector<std::vector<int>> stats;

        public:
           Agents_Map();
//funkcja planisty, gdy wszyscy agenci czekają w miastach na załadunek/rozładuenk planista zostaje
//odblokowany i przydziela wszystkim agentom czasy dostępu do miast
           void scheduler();
           void addMapPoint(int id, std::string name, double ox, double oy);
           void addAgent(int id, std::string origin, std::string destination, int load, int capacity);
           void addPath(int id, int begin, int end, int type);
           void addSpeeds(int v1, int v2, int v3);
           void addLoadingSpeeds(int load, int unload);
           void addAccident(double n, int work_time, int break_time);
//uruchomienie wątków agentów i planisty
           void run();
//przygotowanie do ponownego uruchomienia, przywrócenie do stanu z przed symulacji
           void restart();
//wyczyszczenie danych mapy
           void clean();
           std::string getAgentRoute(int id);
           std::string getAgentRaport(int id);
           std::string getAgentStats(int id, int runs);
           std::string getPaths();
};

#endif
