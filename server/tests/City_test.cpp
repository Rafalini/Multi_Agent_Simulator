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

			BOOST_CHECK_EQUAL(c1.getId(), 0);
    	BOOST_CHECK_EQUAL(c1.getName(), "Warszawa");
	    BOOST_CHECK_EQUAL(c1.getOx(), 1);
	    BOOST_CHECK_EQUAL(c1.getOy(), 2);
}

BOOST_AUTO_TEST_CASE(getsCityTest2)
{
		City *c1 = new City(0,"Krakow", 58, -2);

			BOOST_CHECK_EQUAL(c1->getId(), 0);
			BOOST_CHECK_EQUAL(c1->getName(), "Krakow");
			BOOST_CHECK_EQUAL(c1->getOx(), 58);
			BOOST_CHECK_EQUAL(c1->getOy(), -2);
}


BOOST_AUTO_TEST_CASE(distanceCityTest1)
{
		City c0 (0,"Krakow", 58, -2);

		BOOST_CHECK_EQUAL(c0.getDistanceTo(c0), 0);

		City *c1 = new City(0,"Krakow", 0, 1);
		City *c2 = new City(0,"Warszawa", 1, 1);

		BOOST_CHECK_EQUAL(c1->getDistanceTo(*c2), 1);
}

bool ifConsists(std::vector<Neighbor> v, int id)
{
		auto city = std::find_if(v.begin(), v.end(), [&id](const Neighbor &n)
																							{return n.city->getId() == id;});
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

		Data_table table;
		table.max_speed_0   = 50;
		table.max_speed_1   = 50;
		table.max_speed_2   = 50;

		std::shared_ptr<Road> r = std::make_shared<Road>(0,table);

		c1->addNeighbor(c2,r);  //  c1  ---  c2
		c1->addNeighbor(c4,r);  //  |	   		|
		c2->addNeighbor(c1,r);  //	 |	 	  	|
		c2->addNeighbor(c3,r);  //  c4 --- c3
		c3->addNeighbor(c2,r);
		c3->addNeighbor(c4,r);
		c4->addNeighbor(c3,r);
		c4->addNeighbor(c1,r);
//count test
		BOOST_CHECK_EQUAL(c1->getNeighbors().size(), 2);
		BOOST_CHECK_EQUAL(c2->getNeighbors().size(), 2);
		BOOST_CHECK_EQUAL(c3->getNeighbors().size(), 2);
		BOOST_CHECK_EQUAL(c4->getNeighbors().size(), 2);
//id test
		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c2->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c4->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c1->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c3->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c2->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c4->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c1->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c3->getId()), true);

		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c3->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c4->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c1->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c2->getId()), false);

		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c1->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c2->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c3->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c4->getId()), false);
}

BOOST_AUTO_TEST_CASE(neighboursCityTest2)
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

		c1->addNeighbor(c2,r);  //  c1  ---- c2
		c1->addNeighbor(c4,r);  //  | \____	|
		c2->addNeighbor(c1,r);  //	 |	    \|
		c2->addNeighbor(c3,r);  //  c4 --- c3
		c3->addNeighbor(c2,r);
		c3->addNeighbor(c4,r);
		c4->addNeighbor(c3,r);
		c4->addNeighbor(c1,r);

		c1->addNeighbor(c3,r); //one direction

//count test
		BOOST_CHECK_EQUAL(c1->getNeighbors().size(), 3);
		BOOST_CHECK_EQUAL(c2->getNeighbors().size(), 2);
		BOOST_CHECK_EQUAL(c3->getNeighbors().size(), 2);
		BOOST_CHECK_EQUAL(c4->getNeighbors().size(), 2);
//id test
		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c2->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c4->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c1->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c3->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c2->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c4->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c1->getId()), true);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c3->getId()), true);

		BOOST_CHECK_EQUAL(ifConsists(c1->getNeighbors(),c3->getId()), true);

		BOOST_CHECK_EQUAL(ifConsists(c2->getNeighbors(),c4->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c3->getNeighbors(),c1->getId()), false);
		BOOST_CHECK_EQUAL(ifConsists(c4->getNeighbors(),c2->getId()), false);
}
