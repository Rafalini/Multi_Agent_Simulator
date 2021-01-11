#include "Road.hpp"
#include "Agents_Map.hpp"
#include <iostream>

Road::Road(int conn, data_table limits)
          {
              connection_type = static_cast<connections>(conn);
              //std::cout << conn << " "<<connection_type<<" "<<limits.max_speed_0<<limits.max_speed_1<<limits.max_speed_2<<std::endl;
              switch(connection_type)
          					{
          						case COUNTRY: speed = limits.max_speed_0; break;
          						case EXPRESS: speed = limits.max_speed_1; break;
          						case HIGHWAY: speed = limits.max_speed_2; break;
          					}
          }

connections Road::get_connection_type(){return connection_type;}

int Road::get_speed(){return speed;}
