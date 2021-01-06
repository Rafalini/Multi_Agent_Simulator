#include "Agent.hpp"
#include "City.hpp"
#include <memory>
#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>


Agent::Agent(){}
Agent::Agent(int _id, std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, data_table _table)
																 : agent_id(_id), origin(_origin), destination(_destination), total_load_to_transport(_load), limits(_table){}

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
					std::shared_ptr<City> neighbor = neighbors[i].neighbor;

					if(neighbor->get_id() != previous->get_id() && history.find(neighbor->get_id())==history.end())	{//dont add previously visited node

								double metric = origin->get_distance_to(*neighbor)+		//cost to neighbor
																target->get_distance_to(*neighbor)+		//direction cost
																cost;								//previous cost

								points.push_back(std::make_pair(metric, graph_node(neighbor, origin)));
								history.insert(std::make_pair(neighbor->get_id(),origin->get_id()));
					}
		}
}

void Agent::insert_first_neighbors(std::vector<std::pair<double,graph_node>> &points, std::shared_ptr<City> &origin,
																	 std::shared_ptr<City> &target, std::map<int,int> &history)
{
	std::vector<neighbor> neighbors = origin->get_neighbors();
	for(long unsigned int i=0; i<neighbors.size(); ++i){
				std::shared_ptr<City> neighbor = neighbors[i].neighbor;

				double metric = origin->get_distance_to(*neighbor)+		//cost to neighbor
												target->get_distance_to(*neighbor);		//direction cost
			  points.push_back(std::make_pair(metric, graph_node(neighbor, origin)));
				history.insert(std::make_pair(neighbor->get_id(),origin->get_id()));
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

void Agent::agent_drive(std::shared_ptr<City> position, std::shared_ptr<City> target)
{
		path_finder(position, target);
		std::shared_ptr<City> current_pos = position;

		while(path.size()>1)
		{
			path_finder(current_pos, target);
			double distance, speed;

			std::vector<neighbor> cities = current_pos->get_neighbors();

			for(auto city : cities)
				if(city.neighbor->get_id() == path[path.size()-2])
				{
					distance = city.distance;
					current_pos = city.neighbor;
					switch(city.connection)
					{
						case COUNTRY: speed = limits.max_speed_0; break;
						case EXPRESS: speed = limits.max_speed_1; break;
						case HIGHWAY: speed = limits.max_speed_2; break;
					}
					break;
				}

			std::string information, location;

			if(current_pos->get_name().find("point") != std::string::npos)
				location = "point";
			else
				location = "city";


			information = std::string("{\"state\": ")+
										std::string("\"moving\", ")+
										std::string("\"locationtype\":")+
										"\""+location+"\","+
										std::string("\"locationid\": \"")+ std::to_string(path[path.size()-1])+std::string("\",")+
										std::string("\"duration\": \"")+ std::to_string((int)(speed*distance))+std::string("\"}");
			history.push_back(information);
		}
}

void Agent::agent_load()
{
		if(total_load_to_transport > limits.load_limit)
		{
				current_load = limits.load_limit;
				total_load_to_transport -= limits.load_limit;
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
									std::string("\"locationtype\":")+
									std::string( "\"city\", ")+
									std::string("\"locationid\": \"")+ std::to_string(ori->get_id())+std::string("\",")+
									std::string("\"duration\": \"")+ std::to_string(limits.load_speed*current_load)+std::string("\"}");
		history.push_back(information);
}
void Agent::agent_unload()
{
	std::shared_ptr<City> ori = origin.lock();
	std::string information;
	information = std::string("{\"state\": ")+
								std::string("\"unloading\", ")+
								std::string("\"locationtype\":")+
								std::string( "\"city\", ")+
								std::string("\"locationid\": \"")+ std::to_string(ori->get_id())+std::string("\",")+
								std::string("\"duration\": \"")+ std::to_string(limits.unload_speed*current_load)+std::string("\"}");
  current_load=0;
	history.push_back(information);
}
void Agent::agent_go()
{
		std::shared_ptr<City> starting_city = origin.lock();
		std::shared_ptr<City> ending_city = destination.lock();

		while(total_load_to_transport != 0 && !accident_happened)	{
				agent_load();
		 		agent_drive(starting_city, ending_city);
		 		agent_unload();
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
