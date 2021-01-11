//300190
//Klasa reprezentująca agenta.

#include <memory>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
#include <semaphore.h>
#include <thread>

#include "Agent.hpp"
#include "City.hpp"

Agent::Agent(){} //for tests
Agent::~Agent(){
						sem_destroy(&acces_sem);
						sem_destroy(&break_sem);
					}
Agent::Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, int _cap, Data_table _table)
				: agent_id(_id), origin(_origin), destination(_destination), total_load_to_transport(_load), capacity(_cap), limits(_table)
				{
					if(total_load_to_transport > capacity){
						current_load = capacity;
						total_load_to_transport -= capacity;
					}else{
						current_load = total_load_to_transport;
						total_load_to_transport = 0;
					}

					sem_init(&acces_sem, 0,0);
					sem_init(&break_sem, 0,0);
				}

std::weak_ptr<City> Agent::getOrigin() 			{return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}

int Agent::getTotalLoad() 					{return total_load_to_transport;}
int Agent::getCurrentLoad() 				{return current_load;}
int Agent::getId() 									{return agent_id;}
int Agent::getNumOfBreaks() 				{return num_of_breaks;}
int Agent::getGoodsDelivered() 			{return goods_delivered;}
int Agent::getDistanceMade() 				{return distance_made;}
int Agent::getTotalTimeOnTrack() 	{return total_time_on_track;}
bool Agent::isRunning() 							{return running;}

std::vector<int> Agent::getPath()				{return path;} //ids of nodes

void Agent::insertNeighbors(	std::vector<std::pair<double,Graph_node>> &points, double cost,	Graph_node &node,
															std::shared_ptr<City> &target, std::map<int,int> &history){

						std::shared_ptr<City> origin = node.city.lock();
						std::shared_ptr<City> previous = node.previous.lock();
						std::vector<Neighbor> neighbors = origin->getNeighbors();

						for(int i=0; i<(int)neighbors.size(); ++i){
							std::shared_ptr<City> next_city = neighbors[i].city;
							int speed = neighbors[i].road->getSpeed();

							if(next_city->getId() != previous->getId() && history.find(next_city->getId())==history.end())	{//dont add previously visited node

								double metric = origin->getDistanceTo(*next_city)*City::DISTANCE_PER_UNIT/speed+		//cost to neighbor
																target->getDistanceTo(*next_city)*City::DISTANCE_PER_UNIT/speed+		//direction cost
																cost;								//previous cost

								points.push_back(std::make_pair(metric, Graph_node(next_city, origin)));
								history.insert(std::make_pair(next_city->getId(),origin->getId()));
							}
						}
					}

void Agent::insertFirstNeighbors(std::vector<std::pair<double,Graph_node>> &points, std::shared_ptr<City> &origin,
																	 std::shared_ptr<City> &target, std::map<int,int> &history){

						std::vector<Neighbor> neighbors = origin->getNeighbors();

						for(long unsigned int i=0; i<neighbors.size(); ++i){
							std::shared_ptr<City> next_city = neighbors[i].city;
							int speed = neighbors[i].road->getSpeed();

							double metric = origin->getDistanceTo(*next_city)*City::DISTANCE_PER_UNIT/speed+		//cost to neighbor
															target->getDistanceTo(*next_city)*City::DISTANCE_PER_UNIT/speed;		//direction cost
						  points.push_back(std::make_pair(metric, Graph_node(next_city, origin)));
							history.insert(std::make_pair(next_city->getId(),origin->getId()));
						}
					}

void Agent::pathFinder(std::shared_ptr<City> position, std::shared_ptr<City> target){
						std::vector<std::pair<double,Graph_node>> points; //queue of nodes to be visited
						std::map<int,int> history;				//city, previous_city
						Graph_node current;
						path.clear();

						std::shared_ptr<City> curr_city;
						std::shared_ptr<City> previous;

						if(position->getId() == target->getId()){ //there is no path
							path.push_back(position->getId());
							return;
						}

						insertFirstNeighbors(points, position, target, history); //first set of neighbours

						while(!points.empty()){

							sort(points.begin(), points.end(),
							[](const std::pair<double,Graph_node>&a, const std::pair<double,Graph_node>&b)
							{	return a.first < b.first; }); //sort decreasing

							current = points.begin()->second;
							curr_city = current.city.lock();
							previous = current.previous.lock();

							points.erase(points.begin());

							if(curr_city->getId() == target->getId()) //target found
								break;

							insertNeighbors(points, points.begin()->first, current, target, history);
						}
						//generate path
						int curr_id = curr_city->getId();
						path.push_back(curr_id);

						while(curr_id != position->getId()){ //backward search
							path.push_back( history[curr_id] ); //previous city
							curr_id = history[curr_id];
						}
					}

bool Agent::checkIfAccident(int distance){
						while(distance > 0){
							if((double)std::rand()/(double)RAND_MAX < limits.accident){
								accident_happened=true;
								return true;
							}
							distance -= Agent::accident_rate;
						}
						return false;
					}

void Agent::hitTheRoad(int time_to_travel, Neighbor next_city){
						int time_on_this_route=0;
						if(time_on_track >= limits.non_stop_working_time){ //break in city
							history.push_back(printBreak(next_city.city->getId(), limits.break_time));
							time_on_track = 0;
							++num_of_breaks;
						}

						if(time_to_travel < limits.non_stop_working_time-time_on_track)	{		//no breaks
							history.push_back(printMoving(next_city.city->getId(), time_to_travel));
							distance_made += time_to_travel*next_city.road->getSpeed()/60;
							time_on_track += time_to_travel;
						}else{																														//breaks
							while(time_to_travel > time_on_this_route + limits.non_stop_working_time - time_on_track){
								time_on_this_route += limits.non_stop_working_time-time_on_track;
								history.push_back(printMoving(next_city.city->getId(), time_on_this_route, (double)time_on_this_route/(double)time_to_travel));
								history.push_back(printBreak(next_city.city->getId(), limits.break_time));
								distance_made += time_on_this_route*next_city.road->getSpeed()/60; //mins->hours
								time_on_track = 0;
								++num_of_breaks;
							}
							history.push_back(printMoving(next_city.city->getId(), time_to_travel-time_on_this_route));
							time_on_track += time_to_travel-time_on_this_route;
					  }
						total_time_on_track+=time_to_travel;

						if(total_time_on_track > 60 * 8)
							working_hours = false;
				}


void Agent::agentDrive(std::shared_ptr<City> position, std::shared_ptr<City> target){
					pathFinder(position, target); //fill path for the first time
					std::shared_ptr<City> current_pos = position;

					while(path.size()>1 && !accident_happened && working_hours){
						std::vector<Neighbor> cities = current_pos->getNeighbors();
						int id = path[path.size()-2]; //last id=this node id, last-1 = next node

						auto next_city = std::find_if(cities.begin(), cities.end(), [&id](const Neighbor &n)
																												{return n.city->getId() == id;});
			      if(next_city != cities.end()){
							if(checkIfAccident((int)(next_city->distance*City::DISTANCE_PER_UNIT)))
								history.push_back(printAccident(path[path.size()-2],(int)(next_city->road->getSpeed()*next_city->distance),(double)std::rand()/(double)RAND_MAX));
							else{										// distance_on_map * scale / speed * 60 [for minutes]
								int time_to_travel = current_pos->getDistanceTo(next_city->city)*City::DISTANCE_PER_UNIT/next_city->road->getSpeed()*60;
								hitTheRoad(time_to_travel, *next_city);//jack
								current_pos = next_city->city;
							}
							pathFinder(current_pos, target);
						}
					}
				}

std::string Agent::printMoving(int loc_id, int duration){
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}

std::string Agent::printMoving(int loc_id, int duration, double proc){
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\",")+
												std::string("\"percentage\": \"")+ std::to_string(proc)+std::string("\"}");
				}

std::string Agent::printWaiting(int loc_id, int duration){
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"waiting\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}

std::string Agent::printBreak(int loc_id, int duration){
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"break\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}

std::string Agent::printAccident(int loc_id, int duration, double proc){
					return        std::string("{\"state\": ")+
												std::string("\"accident\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\",")+
												std::string("\"percentage\": \"")+ std::to_string(proc)+std::string("\"}");
				}

void Agent::unlockMutex() { sem_post(&break_sem);}

void Agent::accesSched(){
					 sem_wait(&acces_sem);
					 sem_post(&acces_sem);
				}

void Agent::agentLoad(){
						if(total_load_to_transport > capacity){
							current_load = capacity;
							total_load_to_transport -= capacity;
						}else{
							current_load = total_load_to_transport;
							total_load_to_transport = 0;
						}
						std::shared_ptr<City> ori = origin.lock();

						ori->syncAddToQue(agent_id, actual_time, limits.load_time_per_unit*current_load);
						sem_post(&acces_sem); //enable scheduler
						sem_wait(&break_sem); //wait for cheduler
						sem_wait(&acces_sem);

						int start_time = ori->syncGetStartTime(agent_id);

						if(start_time != actual_time){
							history.push_back(printWaiting(ori->getId(), start_time-actual_time));
							actual_time = start_time;
						}
						std::string information, location;
						information = std::string("{\"state\": ")+
													std::string("\"loading\", ")+
													std::string("\"locationid\": \"")+ std::to_string(ori->getId())+std::string("\",")+
													std::string("\"duration\": \"")+ std::to_string(limits.load_time_per_unit*current_load)+std::string("\"}");
						history.push_back(information);
						time_on_track=0;
						actual_time+=limits.load_time_per_unit*current_load;
				}

void Agent::agentUnload(){
					std::shared_ptr<City> des = destination.lock();

					des->syncAddToQue(agent_id, actual_time, limits.unload_time_per_unit*current_load);
					sem_post(&acces_sem); //enable wake up sched, if waiting wake up
					sem_wait(&break_sem); //wait for cheduler
					sem_wait(&acces_sem);

					int start_time = des->syncGetStartTime(agent_id);

					if(start_time != actual_time){
						history.push_back(printWaiting(des->getId(), start_time-actual_time));
						actual_time = start_time;
					}

					goods_delivered+=current_load;
					std::string information;
					information = std::string("{\"state\": ")+
												std::string("\"unloading\", ")+
												std::string("\"locationid\": \"")+ std::to_string(des->getId())+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(limits.unload_time_per_unit*current_load)+std::string("\"}");
				  current_load=0;
					history.push_back(information);
					actual_time+=limits.load_time_per_unit*current_load;
				}

void Agent::agentGo()		{t = std::thread(&Agent::agentTravel, this);}

void Agent::agentStop()	{t.join();}

void Agent::agentTravel(){
					std::shared_ptr<City> starting_city = origin.lock();
					std::shared_ptr<City> ending_city = destination.lock();

					while((total_load_to_transport != 0 || current_load != 0) && !accident_happened && working_hours)	{
						agentDrive(starting_city, ending_city);

						if(accident_happened || !working_hours)
								break;

						agentUnload();  //break_sem down, sched_sem up

						if(total_load_to_transport != 0){ //if course done, stay in final location
							agentDrive(ending_city, starting_city);

							if(accident_happened || !working_hours)
									break;

							agentLoad(); //break_sem down, sched_sem up
						}
				 }
				 sem_post(&acces_sem); //unlock scheduler on exit from function, forever
				 running = false;
				}


std::string Agent::getHistory(){
					std::string output = "[";
					for(long unsigned int i=0; i<history.size(); i++)
						output += history[i]+", ";
					output = output.substr(0, output.size()-2);
					output += "]";
					return output;
				}

std::string Agent::getRaport(){
					return std::string("\"delivered\": \"")+
								 std::to_string(goods_delivered)+
								 std::string("\", \"working_time\": \"")+
			 					 std::to_string(total_time_on_track)+
								 std::string("\", \"distance\" : \"")+
								 std::to_string(distance_made)+
								 std::string(" km.\"");
				}
