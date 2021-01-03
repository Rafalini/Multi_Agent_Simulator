#define BOOST_TEST_MODULE Agent_test

#include <boost/test/included/unit_test.hpp>
//#include "Agent.hpp"
#include "City.hpp"
//#include <memory>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(AgentTest1)
{
      //std::shared_ptr<City> c1 = std::make_shared<City>(new City(0,"Warszawa", 1.0, 2.0));
			//City c(0,"Warszawa", 1.0, 2.0);
			City c1(0,"Warszawa", 1, 2);

      //std::shared_ptr<City> c2 = std::make_shared<City>(new City("Krakow", 3, 4));
      //Agent a1(c1,c2, 5);
    	//BOOST_CHECK_EQUAL(a1.getLoad(), 5);
	    //BOOST_CHECK_EQUAL(a1.getOrigin(),c1);
	    //BOOST_CHECK_EQUAL(a1.getDestination(),c2);
}

BOOST_AUTO_TEST_CASE(AgentTest2)
{
	   BOOST_CHECK_EQUAL(1,1);
}
