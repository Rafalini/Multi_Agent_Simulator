#include <QtTest>
#include "../../headers/agent.h"
#include "../../headers/point.h"
#include "../../headers/city.h"
#include "../../headers/linesegment.h"

// add necessary includes here

class AgentTest : public QObject
{
    Q_OBJECT

public:
    AgentTest();
    ~AgentTest();

private slots:
    void agentTest();
    void jsonTest();
};

AgentTest::AgentTest()
{

}

AgentTest::~AgentTest()
{

}

void AgentTest::agentTest() {
    QString beg = "Kraków";
    QString des = "Warszawa";
    double weight = 2.15;
    City begining(beg, 0, 0);
    City destination(des, 0, 0);
    Agent *agent = new Agent(&begining, &destination, weight);

    QSignalSpy spyEdited(agent, SIGNAL(edited()));
    QSignalSpy spyDeleted(agent, SIGNAL(deleted()));

    QCOMPARE(agent->getBegining(), &begining);
    QCOMPARE(agent->getDestination(), &destination);
    QCOMPARE(agent->getWeight(), weight);

    QString newBeg = "Katowice";
    QString newDes = "Wrocław";
    City newBegining(newBeg, 0, 0);
    City newDestination(newBeg, 0, 0);
    double newWeight = 1000.75;

    QCOMPARE(spyEdited.count(), 0);
    agent->update(&newBegining, &newDestination, newWeight);
    QCOMPARE(spyEdited.count(), 1);
    QCOMPARE(agent->getBegining(), &newBegining);
    QCOMPARE(agent->getDestination(), &newDestination);
    QCOMPARE(agent->getWeight(), newWeight);
    QCOMPARE(spyDeleted.count(), 0);
    delete agent;
    QCOMPARE(spyDeleted.count(), 1);
    QCOMPARE(spyEdited.count(), 1);
}

void AgentTest::jsonTest() {
    QString beg = "Kraków";
    QString des = "Warszawa";
    double weight = 2.15;
    City begining(beg, 0, 0);
    City destination(des, 0, 0);
    QJsonObject comparableJson;
    comparableJson["begining"] = begining.getName();
    comparableJson["destination"] = destination.getName();
    comparableJson["weight"] = weight;
    Agent agent(&begining, &destination, weight);
    QCOMPARE(agent.tojSON(), comparableJson);
}

QTEST_APPLESS_MAIN(AgentTest)

#include "tst_agenttest.moc"
