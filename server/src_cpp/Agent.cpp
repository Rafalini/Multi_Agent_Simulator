#include "Agent.hpp"
#include "City.hpp"
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>


Agent::Agent(){}
Agent::Agent(std::shared_ptr<City> _origin, std::shared_ptr<City> _destination, int _load, data_table _table)
																 : limits(_table), origin(_origin), destination(_destination), total_load_to_transport(_load){}

std::weak_ptr<City> Agent::getOrigin() {return origin;}
std::weak_ptr<City> Agent::getDestination() {return destination;}
int Agent::getLoad() {return total_load_to_transport;}
int Agent::get_id() {return agent_id;}

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

		std::shared_ptr<City> curr_city;
		std::shared_ptr<City> previous;

		insert_first_neighbors(points, position, target, history); //first set of neighbours

		while(!points.empty()){

				sort(points.begin(), points.end(),
				[](const std::pair<double,graph_node>&a, const std::pair<double,graph_node>&b)
				{	return a.first > b.first; });

				current = points.begin()->second;
				curr_city = current.city.lock();
				previous = current.previous.lock();

				points.erase(points.begin());

				if(curr_city->get_id() == target->get_id()) //target found
						break;

				insert_neighbors(points, points.begin()->first, current, target, history);
		}
//generate path
		path.clear();
		int curr_id = curr_city->get_id();
		path.push_back(curr_id);
		while(curr_id != position->get_id()) //backward search
		{
				path.push_back( history[curr_id] ); //previous city
				curr_id = history[curr_id];
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
