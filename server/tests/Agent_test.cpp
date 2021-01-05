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

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder1)
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
    std::vector<int> path;
		Agent a;
    a.path_finder(c1,c3);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c3 <- c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 3);
    BOOST_CHECK_EQUAL(path[0], 2);
    BOOST_CHECK_EQUAL(path[1], 1);
    BOOST_CHECK_EQUAL(path[2], 0);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder2)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 0, 20);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 2, 2);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		c1->add_neighbor(c2,0);  //  c1  --------- c2
		c1->add_neighbor(c4,0);  //   \	   		     |
		c2->add_neighbor(c1,0);  //	   \	    	  |
		c2->add_neighbor(c3,0);  //     c4 --- c3
		c3->add_neighbor(c2,0);  //
		c3->add_neighbor(c4,0);  //
		c4->add_neighbor(c3,0);  //
		c4->add_neighbor(c1,0);  //

		std::vector<std::pair<double,graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.path_finder(c1,c3);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c3 <- c4 <- c1
    BOOST_CHECK_EQUAL(path.size(), 3);
    BOOST_CHECK_EQUAL(path[0], 2);
    BOOST_CHECK_EQUAL(path[1], 3);
    BOOST_CHECK_EQUAL(path[2], 0);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder3)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 0, 2);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 2, 2);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		c1->add_neighbor(c2,0);  //  c1
		c2->add_neighbor(c1,0);  //   |
    c2->add_neighbor(c3,0);  //  c2
		c3->add_neighbor(c2,0);  //   |
		c3->add_neighbor(c4,0);  //  c3
		c4->add_neighbor(c3,0);  //  |
                             // c4
		std::vector<std::pair<double,graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.path_finder(c1,c4);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c4 <- c3 <- c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 4);
    BOOST_CHECK_EQUAL(path[0], 3);
    BOOST_CHECK_EQUAL(path[1], 2);
    BOOST_CHECK_EQUAL(path[2], 1);
    BOOST_CHECK_EQUAL(path[3], 0);

    a.path_finder(c1,c3);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c3 <- c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 3);
    BOOST_CHECK_EQUAL(path[0], 2);
    BOOST_CHECK_EQUAL(path[1], 1);
    BOOST_CHECK_EQUAL(path[2], 0);

    a.path_finder(c1,c2);               //path from c1 to c2
    path = a.get_path();                //path written backwards: c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 1);
    BOOST_CHECK_EQUAL(path[1], 0);

    a.path_finder(c3,c4);               //path from c3 to c4
    path = a.get_path();                //path written backwards: c4 <- c3
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 3);
    BOOST_CHECK_EQUAL(path[1], 2);

    a.path_finder(c2,c2);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c4 <- c3
    BOOST_CHECK_EQUAL(path.size(), 1);
    BOOST_CHECK_EQUAL(path[0], 1);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder4) //big test
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"top-letf", -5, 5);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"top_right", 5, 5);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"top-mid-left", -2, 2);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"top-mid-right", 2, 2);
    std::shared_ptr<City> c5 = std::make_shared<City>(0,"dow-mid-left", -2, -2);
    std::shared_ptr<City> c6 = std::make_shared<City>(1,"dow-mid-right", 2, -2);
    std::shared_ptr<City> c7 = std::make_shared<City>(2,"dow-left", -5, -5);
    std::shared_ptr<City> c8 = std::make_shared<City>(3,"dow-right", 5, -5);

		c1->add_neighbor(c2,0);  //
		c2->add_neighbor(c1,0);  //

		std::vector<std::pair<double,graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.path_finder(c1,c2);               //path from c1 to c3
    path = a.get_path();                //path written backwards: c3 <- c4 <- c1
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 1);
    BOOST_CHECK_EQUAL(path[1], 0);
}

BOOST_AUTO_TEST_CASE(agent_route_test)
{
    std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 1, 2);
    std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 3, 4);

    c1->add_neighbor(c2,0);  //
		c2->add_neighbor(c1,0);  //

    data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;
    table.accident      = 0.1;
    table.step          = 0.00001;
    table.load_speed    = 1;
    table.unload_speed  = 1;
    table.load_limit    = 5;

    Agent a(c1,c2, 10, table);
    a.agent_go();
    std::cout << a.get_history() << std::endl;
}
