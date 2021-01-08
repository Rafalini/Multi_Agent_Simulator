#include <QtTest>
#include "tst_agentstests.hpp"
#include "tst_pathtests.hpp"
#include "tst_agenttest.hpp"
#include "tst_pointtests.hpp"
#include "tst_citytests.hpp"


int main(int argc, char *argv[])
{
   int status = 0;

   {
      AgentsTests agentsTest;
       status |= QTest::qExec(&agentsTest, argc, argv);
   }

   {
       AgentTest agentTest;
       status |= QTest::qExec(&agentTest, argc, argv);
   }

   {
       PathTests pathTests;
       status |= QTest::qExec(&pathTests, argc, argv);
   }


   {
       PointTests pointTests;
       status |= QTest::qExec(&pointTests, argc, argv);
   }


   {
       CityTests cityTests;
       status |= QTest::qExec(&cityTests, argc, argv);
   }

   return status;
}
