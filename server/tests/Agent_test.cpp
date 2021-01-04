#define BOOST_TEST_MODULE Agent_test

#include <boost/test/included/unit_test.hpp>
#include "Agent.hpp"
#include "City.hpp"
#include <memory>
#include <map>
#include <iostream>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(basicAgentTest)
{
      std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 1, 2);
      std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 3, 4);

			data_table table;
			table.max_speed_0   = 50;
			table.max_speed_1   = 50;
			table.max_speed_2   = 50;
			table.accident      = 0.1;
			table.step          = 0.00001;
			table.load_speed    = 1;
			table.unload_speed  = 1;

      Agent a1(c1,c2, 5, table);
    	BOOST_CHECK_EQUAL(a1.getLoad(), 5);
}

BOOST_AUTO_TEST_CASE(pathTest1_nodeInserts)
{
		 std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		 std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		 std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		 std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		 c1->add_neighbor(c2,0);  //  c1  ---  c2
		 c1->add_neighbor(c4,0);  //  |	   		|
		 c2->add_neighbor(c1,0);  //	|	 	  	|
		 c2->add_neighbor(c3,0);  //  c4 --- c3
		 c3->add_neighbor(c2,0);
		 c3->add_neighbor(c4,0);
		 c4->add_neighbor(c3,0);
		 c4->add_neighbor(c1,0);

		 std::vector<std::pair<double,graph_node>> map;
		 std::map<int,int> history;
		 Agent a;
		 a.insert_first_neighbors(map, c1, c1, history);
//two neighbors
	   BOOST_CHECK_EQUAL(map.size(),2);
		std::shared_ptr<City> c11 = map[0].second.city.lock();
		std::shared_ptr<City> c12 = map[1].second.city.lock();

		BOOST_CHECK_EQUAL(c11->get_id(),1);
		BOOST_CHECK_EQUAL(c12->get_id(),3);

		map.clear();
		history.clear();
		a.insert_first_neighbors(map, c4, c4, history);
		c11 = map[0].second.city.lock();
		c12 = map[1].second.city.lock();

		BOOST_CHECK_EQUAL(c11->get_id(),2);
		BOOST_CHECK_EQUAL(c12->get_id(),0);
}

BOOST_AUTO_TEST_CASE(pathTest2_nodeInserts2)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		c1->add_neighbor(c2,0);  //  c1  ---  c2
		c1->add_neighbor(c4,0);  //  |	   		|
		c2->add_neighbor(c1,0);  //	 | 	    	|
		c2->add_neighbor(c3,0);  //  c4 --- c3
		c3->add_neighbor(c2,0);
		c3->add_neighbor(c4,0);
		c4->add_neighbor(c3,0);
		c4->add_neighbor(c1,0);

		std::vector<std::pair<double,graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
		Agent a;
		a.insert_first_neighbors(map, c1, c3, history);
		BOOST_CHECK_EQUAL(map.size(),2);
	  a.insert_neighbors(map, 0.0, map[0].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
		a.insert_neighbors(map, 0.0, map[1].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
		a.insert_neighbors(map, 0.0, map[2].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
}
