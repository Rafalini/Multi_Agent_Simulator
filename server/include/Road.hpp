#ifndef ROAD
#define ROAD

#include <string>
#include <vector>
#include <memory>
#include "Agent.hpp"

enum connections {COUNTRY=0,EXPRESS,HIGHWAY};

struct data_table;

class Road{

    connections connection_type;
    int speed;
  public:
      Road(int conn, data_table limits);
      int get_speed();
      connections get_connection_type();
};

#endif
