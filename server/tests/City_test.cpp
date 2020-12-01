#define BOOST_TEST_MODULE City_test

#include <boost/test/included/unit_test.hpp>
#include "City.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(CityTest1)
{
			City c1("Warszawa", 1, 2);

    	BOOST_CHECK_EQUAL(c1.get_name(), "Warszawa");
	    BOOST_CHECK_EQUAL(c1.get_ox(), 1);
	    BOOST_CHECK_EQUAL(c1.get_oy(), 2);
}

BOOST_AUTO_TEST_CASE(CityTest2)
{
		City *c1 = new City("Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c1->get_name(), "Krakow");
		BOOST_CHECK_EQUAL(c1->get_ox(), 58);
		BOOST_CHECK_EQUAL(c1->get_oy(), -2);
}
