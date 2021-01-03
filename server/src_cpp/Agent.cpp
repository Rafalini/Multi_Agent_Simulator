#include "Agent.hpp"
#include "City.hpp"
#include <iostream>
#include <memory>
#include <map>

Agent::Agent(std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, data_table _table)
																 : limits(_table), origin(_origin), destination(_destination), total_load_to_transport(_load){}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return total_load_to_transport;}
int Agent::getID() {return agent_id;}

void Agent::insert_neighbors(	std::map<double,graph_node> &points, double cost,	graph_node node,
															std::shared_ptr<City> &target, std::map<int,int>history)
{
		std::shared_ptr<City> origin = node.city.lock();
		std::shared_ptr<City> previous = node.previous.lock();
		std::vector<neighbor> neighbors = origin->get_neighbors();

		for(int i=0; i<(int)neighbors.size(); ++i){
					std::shared_ptr<City> neighbor = neighbors[i].neighbor;

					if(neighbor->get_id() != previous->get_id() && history.find(neighbor->get_id())!=history.end())	{//dont add previously visited node

								double metric = origin->get_distance_to(*neighbor)+		//cost to neighbor
																target->get_distance_to(*neighbor)+		//direction cost
																cost;								//previous cost

								points.insert(std::make_pair(metric, graph_node(neighbor, origin)));
					}
		}
}

void insert_neighbors(std::map<double,graph_node> &points, std::shared_ptr<City> &origin, std::shared_ptr<City> &target)
{
	std::vector<neighbor> neighbors = origin->get_neighbors();

	for(int i=0; i<(int)neighbors.size(); ++i){
				std::shared_ptr<City> neighbor = neighbors[i].neighbor;
				double metric = origin->get_distance_to(*neighbor)+		//cost to neighbor
												target->get_distance_to(*neighbor);		//direction cost
			  points.insert(std::make_pair(metric, graph_node(neighbor, origin)));
	}
}


void Agent::path_finder(std::shared_ptr<City> position, std::shared_ptr<City> target)
{
		std::map<double, graph_node> points;
		std::map<int,int> pairs;				//city, previous_city
		graph_node current;

		std::shared_ptr<City> curr_city;
		std::shared_ptr<City> previous;

		insert_neighbors(points, position, target); //first set of neighbours

		while(!points.empty()){

				current = points.begin()->second;
				curr_city = current.city.lock();
				previous = current.previous.lock();

				points.erase(points.begin());
				pairs.insert(std::make_pair(curr_city->get_id(),previous->get_id()));

				if(curr_city->get_id() == target->get_id()) //target found
						break;

				insert_neighbors(points, points.begin()->first, current, target,pairs);
		}
//generate path
		path.clear();
		int curr_id = curr_city->get_id();
		path.push_back(curr_id);
		while(curr_id != position->get_id()) //backward search
		{
				path.push_back( pairs[curr_id] ); //previous city
				curr_id = pairs[curr_id];
		}
}

void Agent::agent_transport(){}
void Agent::agent_load(){}
void Agent::agent_unload(){}
void Agent::agent_return(){}
void Agent::agent_go()
{
		while(total_load_to_transport != 0)	{
				agent_load();
		 		agent_transport();
		 		agent_unload();
		 		agent_return();
	 }
}
