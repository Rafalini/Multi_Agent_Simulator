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
    int speed;
  public:
      Road(int conn, Data_table limits);
      int getSpeed();
      connections getConnectionType();
};

#endif
