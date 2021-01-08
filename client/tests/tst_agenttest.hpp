#include <QtTest>
#include "../../headers/agent.h"
#include "../../headers/point.h"
#include "../../headers/city.h"
#include "../../headers/path.h"

// add necessary includes here

class AgentTest : public QObject
{
    Q_OBJECT

public:
    AgentTest()
    {

    }

    ~AgentTest()
    {

    }

private slots:
    void agentTest() {
        QString beg = "Kraków";
        QString des = "Warszawa";
        double load = 2.15;
        double capacity = 1;
        City begining(beg, 0, 0, 0);
        City destination(des, 0, 0, 0);
        Agent *agent = new Agent(&begining, &destination, load, capacity);

        //QSignalSpy spyEdited(agent, SIGNAL(edited()));
        QSignalSpy spyDeleted(agent, SIGNAL(deleted()));

        QCOMPARE(agent->getBegining(), &begining);
        QCOMPARE(agent->getDestination(), &destination);
        QCOMPARE(agent->getLoad(), load);

        QString newBeg = "Katowice";
        QString newDes = "Wrocław";
        City newBegining(newBeg, 0, 0, 0);
        City newDestination(newBeg, 0, 0, 0);
        double newWeight = 1000.75;
        double newCapacity = 100;

       // QCOMPARE(spyEdited.count(), 0);
        agent->update(&newBegining, &newDestination, newWeight, newCapacity);
        //QCOMPARE(spyEdited.count(), 1);
        QCOMPARE(agent->getBegining(), &newBegining);
        QCOMPARE(agent->getDestination(), &newDestination);
        QCOMPARE(agent->getLoad(), newWeight);
        QCOMPARE(spyDeleted.count(), 0);
        delete agent;
        QCOMPARE(spyDeleted.count(), 1);
        //QCOMPARE(spyEdited.count(), 1);
    }

    void jsonTest() {
        QString beg = "Kraków";
        QString des = "Warszawa";
        double weight = 2.15;
        double capacity = 1;
        City begining(beg, 0, 0, 0);
        City destination(des, 0, 0, 0);
        QJsonObject comparableJson;
        comparableJson["begining"] = begining.getName();
        comparableJson["destination"] = destination.getName();
        comparableJson["load"] = weight;
        comparableJson["capacity"] = capacity;
        Agent agent(&begining, &destination, weight, capacity);
        QCOMPARE(agent.tojSON(), comparableJson);
    }
};

