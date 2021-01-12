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
          randomTimes();
        }

connections Road::getConnectionType() {return connection_type;}

int Road::getId()             {return id;}
int Road::getEndTime()        {return end_time;}
int Road::getBeginTime()      {return begin_time;}
double Road::getOveralEfficiency()  {return overal_efficiency;}
double Road::getInTraficEfficiency()  {return in_trafic_efficiency;}

int Road::getSpeed(int time){
        if(begin_time < time && time < end_time)
          return speed*in_trafic_efficiency;
        else
          return speed*overal_efficiency;
      }


void Road::randomTimes(){
        int duration = rand()%(5*60);
        begin_time = rand()%(3*60);
        end_time = begin_time + duration;
        overal_efficiency = 1 - (double)(rand()%30)/100;
        in_trafic_efficiency = 1 - (double)(rand()%50)/100 - overal_efficiency;
      }
