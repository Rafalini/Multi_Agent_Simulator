#ifndef ROAD
#define ROAD

#include <string>
#include <vector>
#include <memory>
#include "Road.hpp"

enum connections {COUNTRY=0,EXPRESS,HIGHWAY};

class Road{

    connections connection_type;
    int speed;
  public:
      Road(int conn);
      int get_speed();
      connections get_connection_type();
};

#endif
