#define BOOST_TEST_MODULE Agent_test

#include <boost/test/included/unit_test.hpp>
#include "Agent.hpp"
#include "City.hpp"
#include "Road.hpp"

#include <memory>
#include <map>
#include <iostream>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(basicAgentTest)
{
      std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 1, 2);
      std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 3, 4);

			Data_table table;

      Agent a1(0,c1,c2, 5, 10, table);
    	BOOST_CHECK_EQUAL(a1.getTotalLoad(), 0); //agent begins with loaded hold
      BOOST_CHECK_EQUAL(a1.getCurrentLoad(), 5);
}

BOOST_AUTO_TEST_CASE(pathTest1_nodeInserts)
{
		 std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		 std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		 std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		 std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

     Data_table table;
     table.max_speed_0   = 50;
     table.max_speed_1   = 50;
     table.max_speed_2   = 50;

     std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		 c1->addNeighbor(c2,r);  //  c1  ---  c2
		 c1->addNeighbor(c4,r);  //  |	   		|
		 c2->addNeighbor(c1,r);  //	|	 	  	|
		 c2->addNeighbor(c3,r);  //  c4 --- c3
		 c3->addNeighbor(c2,r);
		 c3->addNeighbor(c4,r);
		 c4->addNeighbor(c3,r);
		 c4->addNeighbor(c1,r);

		 std::vector<std::pair<double,Graph_node>> map;
		 std::map<int,int> history;
		 Agent a;
		 a.insertFirstNeighbors(map, c1, c1, history);
//two neighbors
	  BOOST_CHECK_EQUAL(map.size(),2);
		std::shared_ptr<City> c11 = map[0].second.city.lock();
		std::shared_ptr<City> c12 = map[1].second.city.lock();

		BOOST_CHECK_EQUAL(c11->getId(),1);
		BOOST_CHECK_EQUAL(c12->getId(),3);

		map.clear();
		history.clear();
		a.insertFirstNeighbors(map, c4, c4, history);
		c11 = map[0].second.city.lock();
		c12 = map[1].second.city.lock();

		BOOST_CHECK_EQUAL(c11->getId(),2);
		BOOST_CHECK_EQUAL(c12->getId(),0);
}

BOOST_AUTO_TEST_CASE(pathTest2_nodeInserts2)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

    Data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;

    std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //  c1  ---  c2
		c1->addNeighbor(c4,r);  //  |	   		|
		c2->addNeighbor(c1,r);  //	 | 	    	|
		c2->addNeighbor(c3,r);  //  c4 --- c3
		c3->addNeighbor(c2,r);
		c3->addNeighbor(c4,r);
		c4->addNeighbor(c3,r);
		c4->addNeighbor(c1,r);

		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
		Agent a;
		a.insertFirstNeighbors(map, c1, c3, history);
		BOOST_CHECK_EQUAL(map.size(),2);
	  a.insertNeighbors(map, 0.0, map[0].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
		a.insertNeighbors(map, 0.0, map[1].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
		a.insertNeighbors(map, 0.0, map[2].second, c3, history);
		BOOST_CHECK_EQUAL(map.size(),3);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder1)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

    Data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;

    std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //  c1  ---  c2
		c1->addNeighbor(c4,r);  //  |	   		|
		c2->addNeighbor(c1,r);  //	 | 	    	|
		c2->addNeighbor(c3,r);  //  c4 --- c3
		c3->addNeighbor(c2,r);
		c3->addNeighbor(c4,r);
		c4->addNeighbor(c3,r);
		c4->addNeighbor(c1,r);

		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.pathFinder(c1,c3);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c3 <- c2 <- c1
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

    Data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;

    std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //  c1  --------- c2
		c1->addNeighbor(c4,r);  //   \	   		     |
		c2->addNeighbor(c1,r);  //	   \	    	  |
		c2->addNeighbor(c3,r);  //     c4 --- c3
		c3->addNeighbor(c2,r);  //
		c3->addNeighbor(c4,r);  //
		c4->addNeighbor(c3,r);  //
		c4->addNeighbor(c1,r);  //

		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.pathFinder(c1,c3);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c3 <- c4 <- c1
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

    Data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;

    std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //  c1
		c2->addNeighbor(c1,r);  //   |
    c2->addNeighbor(c3,r);  //  c2
		c3->addNeighbor(c2,r);  //   |
		c3->addNeighbor(c4,r);  //  c3
		c4->addNeighbor(c3,r);  //  |
                             // c4
		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.pathFinder(c1,c4);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c4 <- c3 <- c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 4);
    BOOST_CHECK_EQUAL(path[0], 3);
    BOOST_CHECK_EQUAL(path[1], 2);
    BOOST_CHECK_EQUAL(path[2], 1);
    BOOST_CHECK_EQUAL(path[3], 0);

    a.pathFinder(c1,c3);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c3 <- c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 3);
    BOOST_CHECK_EQUAL(path[0], 2);
    BOOST_CHECK_EQUAL(path[1], 1);
    BOOST_CHECK_EQUAL(path[2], 0);

    a.pathFinder(c1,c2);               //path from c1 to c2
    path = a.getPath();                //path written backwards: c2 <- c1
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 1);
    BOOST_CHECK_EQUAL(path[1], 0);

    a.pathFinder(c3,c4);               //path from c3 to c4
    path = a.getPath();                //path written backwards: c4 <- c3
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 3);
    BOOST_CHECK_EQUAL(path[1], 2);

    a.pathFinder(c2,c2);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c4 <- c3
    BOOST_CHECK_EQUAL(path.size(), 1);
    BOOST_CHECK_EQUAL(path[0], 1);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinder4)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 0.5, 0.5);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

    Data_table table;
    table.max_speed_0   = 10;
    table.max_speed_1   = 20;
    table.max_speed_2   = 30;

    std::shared_ptr<Road> r1 = std::make_shared<Road>(0,table);
    std::shared_ptr<Road> r2 = std::make_shared<Road>(2,table);

		c1->addNeighbor(c2,r1);  //  c1 --|
		c1->addNeighbor(c4,r2);  //   |	 c2_
		c2->addNeighbor(c1,r1);  //	 | 	    |
		c2->addNeighbor(c3,r1);  //  c4 --- c3
		c3->addNeighbor(c2,r1);
		c3->addNeighbor(c4,r2);
		c4->addNeighbor(c3,r2); //c1 - c2, c2 - c3 are closer, but
		c4->addNeighbor(c1,r2); //c1 - c4, and c4 - c3 connections are faster

		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.pathFinder(c1,c3);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c3 <- c4 <- c1
    BOOST_CHECK_EQUAL(path.size(), 3);
    BOOST_CHECK_EQUAL(path[0], 2);
    BOOST_CHECK_EQUAL(path[1], 3);
    BOOST_CHECK_EQUAL(path[2], 0);
}

BOOST_AUTO_TEST_CASE(pathTest2_pathFinderX) //big test
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"top-letf", -5, 5);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"top_right", 5, 5);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"top-mid-left", -2, 2);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"top-mid-right", 2, 2);
    std::shared_ptr<City> c5 = std::make_shared<City>(0,"dow-mid-left", -2, -2);
    std::shared_ptr<City> c6 = std::make_shared<City>(1,"dow-mid-right", 2, -2);
    std::shared_ptr<City> c7 = std::make_shared<City>(2,"dow-left", -5, -5);
    std::shared_ptr<City> c8 = std::make_shared<City>(3,"dow-right", 5, -5);

    Data_table table;
    table.max_speed_0   = 50;
    table.max_speed_1   = 50;
    table.max_speed_2   = 50;

    std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //
		c2->addNeighbor(c1,r);  //

		std::vector<std::pair<double,Graph_node>> map; //queue of unique points to be visited,
		std::map<int,int> history;
    std::vector<int> path;
		Agent a;
    a.pathFinder(c1,c2);               //path from c1 to c3
    path = a.getPath();                //path written backwards: c3 <- c4 <- c1
    BOOST_CHECK_EQUAL(path.size(), 2);
    BOOST_CHECK_EQUAL(path[0], 1);
    BOOST_CHECK_EQUAL(path[1], 0);
}
