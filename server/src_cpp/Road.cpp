#include "Road.hpp"
Road::Road(int conn)
          {
              connection_type = static_cast<connections>(conn);
              switch(connection_type)
          					{
          						case COUNTRY: speed = 60; break;
          						case EXPRESS: speed = 80; break;
          						case HIGHWAY: speed = 100; break;
          					}
          }

connections Road::get_connection_type(){return connection_type;}

int Road::get_speed(){return speed;}
