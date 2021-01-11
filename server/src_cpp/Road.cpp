//300190
//Klasa reprezentująca drogę.

#include "Road.hpp"
#include "Agents_Map.hpp"

Road::Road(int _id, int conn, Data_table limits):id(_id){

          connection_type = static_cast<connections>(conn);
          switch(connection_type){
      						case COUNTRY: speed = limits.max_speed_0; break;
      						case EXPRESS: speed = limits.max_speed_1; break;
      						case HIGHWAY: speed = limits.max_speed_2; break;
      					}
          efficiency = 1 - (double)(rand()%50)/100;
        }

connections Road::getConnectionType() {return connection_type;}

int Road::getId() {return id;}
int Road::getSpeed() {return speed*efficiency;}
double Road::getEfficiency() {return efficiency;}
