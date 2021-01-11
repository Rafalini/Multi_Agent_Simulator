#include "Agent.hpp"
#include "City.hpp"

#include <memory>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
#include <semaphore.h>
#include <thread>

Agent::Agent(){} //for tests
Agent::Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, int _cap, data_table _table)
				: agent_id(_id), origin(_origin), destination(_destination), total_load_to_transport(_load), capacity(_cap), limits(_table)
				{
					sem_init(&acces_sem, 0,0);
					sem_init(&break_sem, 0,0);
				}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return total_load_to_transport;}
int Agent::get_id() {return agent_id;}
std::vector<int> Agent::get_path() {return path;} //ids of nodes
std::vector<std::string> Agent::get_his() {return history;}
bool Agent::is_running() {return running;}

void Agent::insert_neighbors(	std::vector<std::pair<double,graph_node>> &points, double cost,	graph_node &node,
															std::shared_ptr<City> &target, std::map<int,int> &history)
				{
						std::shared_ptr<City> origin = node.city.lock();
						std::shared_ptr<City> previous = node.previous.lock();
						std::vector<neighbor> neighbors = origin->get_neighbors();

						for(int i=0; i<(int)neighbors.size(); ++i){
									std::shared_ptr<City> next_city = neighbors[i].city;
									int speed = neighbors[i].road->get_speed();

									if(next_city->get_id() != previous->get_id() && history.find(next_city->get_id())==history.end())	{//dont add previously visited node

												double metric = origin->get_distance_to(*next_city)/speed+		//cost to neighbor
																				target->get_distance_to(*next_city)/speed+		//direction cost
																				cost;								//previous cost

												points.push_back(std::make_pair(metric, graph_node(next_city, origin)));
												history.insert(std::make_pair(next_city->get_id(),origin->get_id()));
									}
						}
				}

void Agent::insert_first_neighbors(std::vector<std::pair<double,graph_node>> &points, std::shared_ptr<City> &origin,
																	 std::shared_ptr<City> &target, std::map<int,int> &history)
				{
					std::vector<neighbor> neighbors = origin->get_neighbors();
					for(long unsigned int i=0; i<neighbors.size(); ++i){
								std::shared_ptr<City> next_city = neighbors[i].city;
								int speed = neighbors[i].road->get_speed();

								double metric = origin->get_distance_to(*next_city)/speed+		//cost to neighbor
																target->get_distance_to(*next_city)/speed;		//direction cost
							  points.push_back(std::make_pair(metric, graph_node(next_city, origin)));
								history.insert(std::make_pair(next_city->get_id(),origin->get_id()));
					}
				}

void Agent::path_finder(std::shared_ptr<City> position, std::shared_ptr<City> target)
				{
						std::vector<std::pair<double,graph_node>> points; //queue of nodes to be visited
						std::map<int,int> history;				//city, previous_city
						graph_node current;
						path.clear();

						std::shared_ptr<City> curr_city;
						std::shared_ptr<City> previous;

						if(position->get_id() == target->get_id()){ //there is no path
								path.push_back(position->get_id());
								return;
							}

						insert_first_neighbors(points, position, target, history); //first set of neighbours

						while(!points.empty()){

								sort(points.begin(), points.end(),
								[](const std::pair<double,graph_node>&a, const std::pair<double,graph_node>&b)
								{	return a.first < b.first; }); //sort decreasing

								current = points.begin()->second;
								curr_city = current.city.lock();
								previous = current.previous.lock();

								points.erase(points.begin());

								if(curr_city->get_id() == target->get_id()) //target found
										break;

								insert_neighbors(points, points.begin()->first, current, target, history);
						}
				//generate path
						int curr_id = curr_city->get_id();
						path.push_back(curr_id);
						while(curr_id != position->get_id()) //backward search
						{
								path.push_back( history[curr_id] ); //previous city
								curr_id = history[curr_id];
						}
				}

bool Agent::check_if_accident(int distance)
				{
						while(distance > 0)
						{
							if((double)std::rand()/(double)RAND_MAX < limits.accident){
									accident_happened=true;
									return true;
							}
							distance -= Agent::accident_rate;
						}
						return false;
				}

void Agent::hit_the_road(int time_to_travel, neighbor next_city) //jack
				{
						int time_on_this_route=0;
						if(time_on_track >= limits.non_stop_working_time) //break in city
						{
							history.push_back(print_waiting(next_city.city->get_id(), limits.break_time));
							time_on_track = 0;
						}

						if(time_to_travel < limits.non_stop_working_time-time_on_track)	{		//no breaks
								history.push_back(print_moving(next_city.city->get_id(), time_to_travel));
								distance_made += time_to_travel*next_city.road->get_speed()/60;
								time_on_track += time_to_travel;
						} else {																														//breaks
								while(time_to_travel > time_on_this_route + limits.non_stop_working_time - time_on_track)
								{
									time_on_this_route += limits.non_stop_working_time-time_on_track;
									history.push_back(print_moving(next_city.city->get_id(), time_on_this_route, (double)time_on_this_route/(double)time_to_travel));
									history.push_back(print_waiting(next_city.city->get_id(), limits.break_time));
									distance_made += time_on_this_route*next_city.road->get_speed()/60; //mins-?hours
									time_on_track = 0;
								}
								history.push_back(print_moving(next_city.city->get_id(), time_to_travel-time_on_this_route));
								time_on_track += time_to_travel-time_on_this_route;
					  }

						total_time_on_track+=time_to_travel;
				}


void Agent::agent_drive(std::shared_ptr<City> position, std::shared_ptr<City> target)
				{
					path_finder(position, target); //fill path for the first time
					std::shared_ptr<City> current_pos = position;

					while(path.size()>1 && !accident_happened)
					{
						std::vector<neighbor> cities = current_pos->get_neighbors();
						int id = path[path.size()-2]; //last id=this node id, last-1 = next node

						auto next_city = std::find_if(cities.begin(), cities.end(), [&id](const neighbor &n)
																												{return n.city->get_id() == id;});
			      if(next_city != cities.end()){
							if(check_if_accident((int)(next_city->distance*City::distance_per_unit))){
									history.push_back(print_accident(path[path.size()-2],(int)(next_city->road->get_speed()*next_city->distance)*Agent::time_scale,0.5));
							}	else
							{										// distance_on_map * scale / speed * 60 [for minutes]
								int time_to_travel = current_pos->get_distance_to(next_city->city)*City::distance_per_unit/next_city->road->get_speed()*60;
								hit_the_road(time_to_travel, *next_city);//jack
								current_pos = next_city->city;
							}
							path_finder(current_pos, target);
						}
					}
				}

std::string Agent::print_moving(int loc_id, int duration)
				{
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}
std::string Agent::print_moving(int loc_id, int duration, double proc)
				{
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\",")+
												std::string("\"percentage\": \"")+ std::to_string(proc)+std::string("\"}");
				}
std::string Agent::print_waiting(int loc_id, int duration)
				{
					actual_time += duration;
					return        std::string("{\"state\": ")+
												std::string("\"break\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}

std::string Agent::print_accident(int loc_id, int duration, double proc)
				{
					return        std::string("{\"state\": ")+
												std::string("\"accident\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\",")+
												std::string("\"percentage\": \"")+ std::to_string(proc)+std::string("\"}");
				}

void Agent::unlock_mutex() { sem_post(&break_sem);}
void Agent::acces_sched()
				{
					 sem_wait(&acces_sem);
					 sem_post(&acces_sem);
				}
void Agent::agent_load()
				{
						if(total_load_to_transport > capacity)
						{
								current_load = capacity;
								total_load_to_transport -= capacity;
						}
						else
						{
								current_load = total_load_to_transport;
								total_load_to_transport = 0;
						}
						std::shared_ptr<City> ori = origin.lock();

						ori->sync_add_to_que(agent_id, actual_time, limits.load_time_per_unit*current_load);
						sem_post(&acces_sem); //enable scheduler
						sem_wait(&break_sem); //wait for cheduler
						sem_wait(&acces_sem);

						int start_time = ori->sync_get_start_time(agent_id);

						if(start_time != actual_time){
									history.push_back(print_waiting(ori->get_id(), start_time-actual_time));
									actual_time = start_time;
						}
						std::string information, location;
						information = std::string("{\"state\": ")+
													std::string("\"loading\", ")+
													std::string("\"locationid\": \"")+ std::to_string(ori->get_id())+std::string("\",")+
													std::string("\"duration\": \"")+ std::to_string(limits.load_time_per_unit*current_load)+std::string("\"}");
						history.push_back(information);
						time_on_track=0;
						actual_time+=limits.load_time_per_unit*current_load;
				}

void Agent::agent_unload()
				{
					std::shared_ptr<City> des = destination.lock();

					des->sync_add_to_que(agent_id, actual_time, limits.unload_time_per_unit*current_load);
					sem_post(&acces_sem); //enable wake up sched, if waiting wake up
					sem_wait(&break_sem); //wait for cheduler
					sem_wait(&acces_sem);

					int start_time = des->sync_get_start_time(agent_id);

					if(start_time != actual_time){
								history.push_back(print_waiting(des->get_id(), start_time-actual_time));
								actual_time = start_time;
					}

					goods_delivered+=current_load;
					std::string information;
					information = std::string("{\"state\": ")+
												std::string("\"unloading\", ")+
												std::string("\"locationid\": \"")+ std::to_string(des->get_id())+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(limits.unload_time_per_unit*current_load)+std::string("\"}");
				  current_load=0;
					history.push_back(information);
					actual_time+=limits.load_time_per_unit*current_load;
				}

void Agent::agent_go()
				{
						t = std::thread(&Agent::agent_travel, this);
				}

void Agent::agent_stop()
				{
						t.join();
				}

void Agent::agent_travel()
				{
					std::shared_ptr<City> starting_city = origin.lock();
					std::shared_ptr<City> ending_city = destination.lock();

					while(total_load_to_transport != 0 && !accident_happened)	{
							agent_load(); //break_sem down, sched_sem up
							std::cout << total_time_on_track << " czas pracy agenta"<<std::endl;
							agent_drive(starting_city, ending_city);
							std::cout << total_time_on_track << " czas pracy agenta"<<std::endl;

							if(accident_happened)
									break;
							agent_unload();  //break_sem down, sched_sem up
							if(total_load_to_transport != 0) //if course done, stay in final location
								agent_drive(ending_city, starting_city);
				 }
				 std::cout << "exit reason: "<<total_load_to_transport<<" acc: "<<accident_happened << std::endl;
				 sem_post(&acces_sem); //unlock scheduler on exit from function, forever
				 running = false;
				}


std::string Agent::get_history()
				{
					std::string output = "[";
					for(long unsigned int i=0; i<history.size(); i++)
								output += history[i]+", ";
					output = output.substr(0, output.size()-2);
					output += "]";
					return output;
				}

std::string Agent::get_raport()
				{
					return std::string("\"delivered\": \"")+
								 std::to_string(goods_delivered)+
								 std::string("\", \"working_time\": \"")+
			 					 std::to_string(total_time_on_track)+
								 std::string("\", \"distance\" : \"")+
								 std::to_string((int)distance_made)+
								 std::string(" km.\"");
				}
