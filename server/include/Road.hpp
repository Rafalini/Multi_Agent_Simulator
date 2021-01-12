//300190
//Klasa reprezentująca drogę.

#ifndef ROAD
#define ROAD

#include <string>
#include <vector>
#include <memory>
#include "Agent.hpp"

enum connections {COUNTRY=0,EXPRESS,HIGHWAY};

struct Data_table;

class Road{

    connections connection_type;
    int id;
    int begin_time;
    int end_time;
    double overal_efficiency;
    double in_trafic_efficiency;

    int speed;
  public:
      Road(int id, int conn, Data_table limits);
      int getSpeed(int time);
      int getId();
      int getEndTime();
      int getBeginTime();
      double getOveralEfficiency();
      double getInTraficEfficiency();
      connections getConnectionType();

      void randomTimes();
};

#endif
