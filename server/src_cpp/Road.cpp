//300190
//Klasa reprezentująca drogę. W zależności od czasu kiedy agent nią jedzie może mieć korek lub nie.
//Służy do podawanie prędkości w zależności od agenta i jego godziny.

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
double Road::getOveralEfficiency()    {return overal_efficiency;}
double Road::getInTraficEfficiency()  {return in_trafic_efficiency;}

int Road::getSpeed(int time){
        if(begin_time < time && time < end_time)
          return speed*in_trafic_efficiency;
        else
          return speed*overal_efficiency;
      }


void Road::randomTimes(){
        int trafic_probability; //int %
        switch(connection_type){
                case COUNTRY: trafic_probability = 80; break;
                case EXPRESS: trafic_probability = 50; break;
                case HIGHWAY: trafic_probability = 20; break;
              }
        if(random()%100<trafic_probability){
          int duration = 2*60 + rand()%(2*60);
          begin_time = 30+rand()%(Agent::SIMULATION_TIME-3*60);

          if(begin_time + duration > Agent::SIMULATION_TIME)
            end_time = Agent::SIMULATION_TIME;
          else
            end_time = begin_time + duration;

          overal_efficiency = 1 - (double)(rand()%10)/100;      //<0.9-1> efficiency -> 90%-100%
          in_trafic_efficiency = 0.3 - (double)(rand()%20)/100; //<0.1-0.3> efficiency -> 10%-30%
        }else{
          end_time=0; //no trafic
          overal_efficiency = 1;
          in_trafic_efficiency = 1;
        }
      }
