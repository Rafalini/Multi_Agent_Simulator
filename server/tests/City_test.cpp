#define BOOST_TEST_MODULE City_test

#include <boost/test/included/unit_test.hpp>
#include "City.hpp"
#include "Agent.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(generalCityTest1)
{
			City c1(0,"Warszawa", 1, 2);

			BOOST_CHECK_EQUAL(c1.get_id(), 0);
    	BOOST_CHECK_EQUAL(c1.get_name(), "Warszawa");
	    BOOST_CHECK_EQUAL(c1.get_ox(), 1);
	    BOOST_CHECK_EQUAL(c1.get_oy(), 2);
}

BOOST_AUTO_TEST_CASE(generalCityTest2)
{
		City *c1 = new City(0,"Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c1->get_id(), 0);
		BOOST_CHECK_EQUAL(c1->get_name(), "Krakow");
		BOOST_CHECK_EQUAL(c1->get_ox(), 58);
		BOOST_CHECK_EQUAL(c1->get_oy(), -2);
}


BOOST_AUTO_TEST_CASE(distanceCityTest1)
{
		City c1 (0,"Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c1.get_distance_to(c1), 0);
}

BOOST_AUTO_TEST_CASE(distanceCityTes21)
{
		City *c1 = new City(0,"Krakow", 0, 1);
		City *c2 = new City(0,"Krakow", 1, 1);

		BOOST_CHECK_EQUAL(c1->get_distance_to(*c2), 1);

		c1 = new City(0,"Krakow", 7, 0);
		c2 = new City(0,"Krakow", 0, 0);

		BOOST_CHECK_EQUAL(c1->get_distance_to(*c2), 7);
}
