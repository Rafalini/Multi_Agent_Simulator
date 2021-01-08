#include "Agent.hpp"
#include "City.hpp"

#include <memory>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>

Agent::Agent(){}
Agent::Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, int _cap, data_table _table)
				: agent_id(_id), origin(_origin), destination(_destination), total_load_to_transport(_load), capacity(_cap), limits(_table){}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return total_load_to_transport;}
int Agent::get_id() {return agent_id;}
std::vector<int> Agent::get_path() {return path;} //ids of nodes
std::vector<std::string> Agent::get_his() {return history;}


void Agent::insert_neighbors(	std::vector<std::pair<double,graph_node>> &points, double cost,	graph_node &node,
															std::shared_ptr<City> &target, std::map<int,int> &history)
				{
						std::shared_ptr<City> origin = node.city.lock();
						std::shared_ptr<City> previous = node.previous.lock();
						std::vector<neighbor> neighbors = origin->get_neighbors();

						for(int i=0; i<(int)neighbors.size(); ++i){
									std::shared_ptr<City> next_city = neighbors[i].city;

									if(next_city->get_id() != previous->get_id() && history.find(next_city->get_id())==history.end())	{//dont add previously visited node

												double metric = origin->get_distance_to(*next_city)+		//cost to neighbor
																				target->get_distance_to(*next_city)+		//direction cost
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

								double metric = origin->get_distance_to(*next_city)+		//cost to neighbor
																target->get_distance_to(*next_city);		//direction cost
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
							if(std::rand()%100 < limits.accident){
									accident_happened=true;
									return true;
							}
							distance -= Agent::accident_rate;
						}
						return false;
				}

void Agent::hit_the_road(double distance, neighbor next_city) //jack
				{
					double current_progress=0, duration=0; //distance
					int move_duration;
					while(current_progress < distance)
						if(time_on_track == limits.non_stop_working_time)
						{
							move_duration = (int)((current_progress-duration)*City::distance_per_unit/next_city.road->get_speed());
							history.push_back(print_moving(next_city.city->get_id(), move_duration, current_progress/distance));
							history.push_back(print_waiting(next_city.city->get_id(), limits.break_time));
							duration = current_progress;
							time_on_track = 0;
						}else{
							++time_on_track;
							distance_made += next_city.road->get_speed();
							double next_step = (double)next_city.road->get_speed() / (double)City::distance_per_unit;

							if(distance < current_progress + next_step){
									move_duration = (int)((10*distance-current_progress)*City::distance_per_unit/next_city.road->get_speed());
									history.push_back(print_moving(next_city.city->get_id(), move_duration));
									break;
							}else
									current_progress += next_step;
						}
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
							{
								hit_the_road(current_pos->get_distance_to(next_city->city), *next_city);//jack
								//history.push_back(print_moving(path[path.size()-2], 50));
								current_pos = next_city->city;
							}
							path_finder(current_pos, target);
						}
					}
				}

std::string Agent::print_moving(int loc_id, int duration)
				{
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\"}");
				}
std::string Agent::print_moving(int loc_id, int duration, double proc)
				{
					return        std::string("{\"state\": ")+
												std::string("\"moving\", ")+
												std::string("\"locationid\": \"")+ std::to_string(loc_id)+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(duration)+std::string("\",")+
												std::string("\"percentage\": \"")+ std::to_string(proc)+std::string("\"}");
				}
std::string Agent::print_waiting(int loc_id, int duration)
				{
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
						std::string information, location;
						information = std::string("{\"state\": ")+
													std::string("\"loading\", ")+
													std::string("\"locationid\": \"")+ std::to_string(ori->get_id())+std::string("\",")+
													std::string("\"duration\": \"")+ std::to_string(limits.load_time_per_unit*current_load)+std::string("\"}");
						history.push_back(information);
						time_on_track=0;
				}

void Agent::agent_unload()
				{
					goods_delivered+=current_load;
					std::shared_ptr<City> ori = destination.lock();
					std::string information;
					information = std::string("{\"state\": ")+
												std::string("\"unloading\", ")+
												std::string("\"locationid\": \"")+ std::to_string(ori->get_id())+std::string("\",")+
												std::string("\"duration\": \"")+ std::to_string(limits.unload_time_per_unit*current_load)+std::string("\"}");
				  current_load=0;
					history.push_back(information);
					time_on_track=0;
				}

void Agent::agent_go()
				{
						std::shared_ptr<City> starting_city = origin.lock();
						std::shared_ptr<City> ending_city = destination.lock();

						while(total_load_to_transport != 0 && !accident_happened)	{
								agent_load();
						 		agent_drive(starting_city, ending_city);

								if(accident_happened)
										break;

						 		agent_unload();

								if(total_load_to_transport != 0) //if course done, stay in final location
						 			agent_drive(ending_city, starting_city);
					 }
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
								 std::string("\", \"distance\" : \"")+
								 std::to_string((int)distance_made)+
								 std::string(" km.\"");
				}
