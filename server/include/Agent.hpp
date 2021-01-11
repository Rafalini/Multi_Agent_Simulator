//300190
//Klasa reprezentująca agenta.

#ifndef AGENT
#define AGENT

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "City.hpp"
#include <semaphore.h>
#include <thread>

class City;
struct Neighbor;
// Struktura reprezentująca odwiedzony węzeł w grafie. Przechowuje odwiedzony węzeł wraz z jego poprzednikiem.
struct Graph_node{
  std::weak_ptr<City> city;
  std::weak_ptr<City> previous;

  Graph_node(std::weak_ptr<City> _city, std::weak_ptr<City> _previous)
    : city(_city), previous(_previous) {}
  Graph_node(std::weak_ptr<City> _city)
      : city(_city) {}
  Graph_node(){}
};
// Struktura z danymi do symulacji, są to ogólne wielkości definiowane przez użytkownika
struct Data_table{
  int max_speed_0;
  int max_speed_1;
  int max_speed_2;

  double accident;

  int load_time_per_unit;
  int unload_time_per_unit;

  int non_stop_working_time;
  int break_time;
};

class Agent{
    private:
        static const int accident_rate = 100; //częśtotliwość wypadków, co jaki dystans wypadek może się zdarzyć

        std::thread t;

        int agent_id;
        std::weak_ptr<City> origin;
        std::weak_ptr<City> destination;
        int total_load_to_transport;
        int capacity;
        int current_load=0;
        int time_on_track=0; //minutes
        int actual_time=0;   //minutes

        Data_table limits;
        //statistics
        int num_of_breaks=0;
        int goods_delivered=0;
        int distance_made=0;
        int total_time_on_track=0;

        std::vector<int> path;            //aktualna ścieżka (kolekcja identyfikatorów kolejnych węzłów)
        std::vector<std::string> history; //spis kolejnych akcji agenta takich jak załadunek, podróż, oczekiwanie etc
        bool accident_happened = false;
        bool running = true;
        bool working_hours = true;

//funkcje wypisujące daną akcję agenta w formacie JSON
        std::string printMoving(int loc_id, int duration);
        std::string printMoving(int loc_id, int duration, double procent);
        std::string printWaiting(int loc_id, int duration);
        std::string printBreak(int loc_id, int duration);
        std::string printAccident(int loc_id, int duration, double procent);

        bool checkIfAccident(int distance);

        sem_t acces_sem;
        sem_t break_sem;
public:

//metody publiczne ze względu na testy, nie są wykorzystywane poza testami
        void pathFinder(std::shared_ptr<City> origin, std::shared_ptr<City> destination);
        void insertFirstNeighbors(std::vector<std::pair<double,Graph_node>> &points, std::shared_ptr<City> &origin, std::shared_ptr<City> &target, std::map<int,int> &history);
        void insertNeighbors(std::vector<std::pair<double,Graph_node>> &points, double cost,	Graph_node &node,	std::shared_ptr<City> &target, std::map<int,int>&history);
        void agentLoad();
        void agentUnload();
        //przemieszczanie agenta po grafie
        void agentDrive(std::shared_ptr<City> position, std::shared_ptr<City> target);
        //przemieszczanie agenta między wierzchołkami, uwzględnia sprawdzanie czasu agenta, przerw etc
        void hitTheRoad(int time, Neighbor next_city);//jack

        std::vector<int> getPath();
        Agent(); //do testowania funkcji grafowych

//metody wykorzystywane publicznie
        Agent(int id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, int _capacity, Data_table _table);
        ~Agent();
        std::weak_ptr<City> getOrigin();
        std::weak_ptr<City> getDestination();
        int getTotalLoad();
        int getCurrentLoad();
        int getId();
        int getNumOfBreaks();
        int getGoodsDelivered();
        int getDistanceMade();
        int getTotalTimeOnTrack();
//uruchamianie wątku agenta
        void agentGo();
//zatrzymywanie wątku agenta
        void agentStop();
//symulacja działań agenta, podróż, załądunek, rozładunek i sprawdzanie warunków
        void agentTravel();
        std::string getHistory();
        std::string getRaport();
//zwalnianie blokady agenta na której agent się zatrzymuje przed zaplanowanie kolejności dostępu do miasta przez planistę
        void unlockMutex();
//zwalnianie blokady planisty, następuje gdy agenci oczekują w miastach na przydział miejsca w kolejce dostępu
        void accesSched();
//sprawdzenie czy agent jeszcze kursuje, czy nie skonczył pracy, jeśli skończył nie blokuje planisty
        bool isRunning();
};

#endif
