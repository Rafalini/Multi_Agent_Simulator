#define BOOST_TEST_MODULE City_test

#include <boost/test/included/unit_test.hpp>
#include "City.hpp"
#include "Road.hpp"

#include <memory>
#include <vector>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(getsCityTest1)
{
			City c1(0,"Warszawa", 1, 2);

			BOOST_CHECK_EQUAL(c1.get_id(), 0);
    	BOOST_CHECK_EQUAL(c1.get_name(), "Warszawa");
	    BOOST_CHECK_EQUAL(c1.get_ox(), 1);
	    BOOST_CHECK_EQUAL(c1.get_oy(), 2);
}

BOOST_AUTO_TEST_CASE(getsCityTest2)
{
		City *c1 = new City(0,"Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c1->get_id(), 0);
		BOOST_CHECK_EQUAL(c1->get_name(), "Krakow");
		BOOST_CHECK_EQUAL(c1->get_ox(), 58);
		BOOST_CHECK_EQUAL(c1->get_oy(), -2);
}


BOOST_AUTO_TEST_CASE(distanceCityTest1)
{
		City c0 (0,"Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c0.get_distance_to(c0), 0);

		City *c1 = new City(0,"Krakow", 0, 1);
		City *c2 = new City(0,"Warszawa", 1, 1);

		BOOST_CHECK_EQUAL(c1->get_distance_to(*c2), 1);

		c1 = new City(0,"Krakow", 7, 0);
		c2 = new City(0,"Warszawa", 0, 0);
}

bool if_consists(std::vector<neighbor> v, int id)
{
		auto city = std::find_if(v.begin(), v.end(), [&id](const neighbor &n)
																							{return n.city->get_id() == id;});
		if(city != v.end())
			return true;
		else
			return false;
}

BOOST_AUTO_TEST_CASE(neighboursCityTest1)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		data_table table;
		table.max_speed_0   = 50;
		table.max_speed_1   = 50;
		table.max_speed_2   = 50;

		std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->add_neighbor(c2,r);  //  c1  ---  c2
		c1->add_neighbor(c4,r);  //  |	   		|
		c2->add_neighbor(c1,r);  //	 |	 	  	|
		c2->add_neighbor(c3,r);  //  c4 --- c3
		c3->add_neighbor(c2,r);
		c3->add_neighbor(c4,r);
		c4->add_neighbor(c3,r);
		c4->add_neighbor(c1,r);
//count test
		BOOST_CHECK_EQUAL(c1->get_neighbors().size(), 2);
		BOOST_CHECK_EQUAL(c2->get_neighbors().size(), 2);
		BOOST_CHECK_EQUAL(c3->get_neighbors().size(), 2);
		BOOST_CHECK_EQUAL(c4->get_neighbors().size(), 2);
//id test
		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c2->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c4->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c1->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c3->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c2->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c4->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c1->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c3->get_id()), true);

		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c3->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c4->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c1->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c2->get_id()), false);

		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c1->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c2->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c3->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c4->get_id()), false);
}

BOOST_AUTO_TEST_CASE(neighboursCityTest2)
{
		std::shared_ptr<City> c1 = std::make_shared<City>(0,"Warszawa", 0, 0);
		std::shared_ptr<City> c2 = std::make_shared<City>(1,"Krakow", 1, 0);
		std::shared_ptr<City> c3 = std::make_shared<City>(2,"Warszawa2", 0, 1);
		std::shared_ptr<City> c4 = std::make_shared<City>(3,"Krakow2", 1, 1);

		data_table table;
		table.max_speed_0   = 50;
		table.max_speed_1   = 50;
		table.max_speed_2   = 50;

		std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->add_neighbor(c2,r);  //  c1  ---- c2
		c1->add_neighbor(c4,r);  //  | \____	|
		c2->add_neighbor(c1,r);  //	 |	    \|
		c2->add_neighbor(c3,r);  //  c4 --- c3
		c3->add_neighbor(c2,r);
		c3->add_neighbor(c4,r);
		c4->add_neighbor(c3,r);
		c4->add_neighbor(c1,r);

		c1->add_neighbor(c3,r); //one direction

//count test
		BOOST_CHECK_EQUAL(c1->get_neighbors().size(), 3);
		BOOST_CHECK_EQUAL(c2->get_neighbors().size(), 2);
		BOOST_CHECK_EQUAL(c3->get_neighbors().size(), 2);
		BOOST_CHECK_EQUAL(c4->get_neighbors().size(), 2);
//id test
		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c2->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c4->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c1->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c3->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c2->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c4->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c1->get_id()), true);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c3->get_id()), true);

		BOOST_CHECK_EQUAL(if_consists(c1->get_neighbors(),c3->get_id()), true);

		BOOST_CHECK_EQUAL(if_consists(c2->get_neighbors(),c4->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c3->get_neighbors(),c1->get_id()), false);
		BOOST_CHECK_EQUAL(if_consists(c4->get_neighbors(),c2->get_id()), false);
}
