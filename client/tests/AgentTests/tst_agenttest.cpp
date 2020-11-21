#include <QtTest>
#include "../../headers/agent.h"

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
    QString begining = "Kraków";
    QString destination = "Warszawa";
    double weight = 2.15;
    Agent *agent = new Agent(begining, destination, weight);
    QSignalSpy spyEdited(agent, SIGNAL(edited()));
    QSignalSpy spyDeleted(agent, SIGNAL(deleted()));

    QCOMPARE(agent->getBegining(), begining);
    QCOMPARE(agent->getDestination(), destination);
    QCOMPARE(agent->getWeight(), weight);

    QString newBegining = "Katowice";
    QString newDestination = "Wrocław";
    double newWeight = 1000.75;

    QCOMPARE(spyEdited.count(), 0);
    agent->update(newBegining, newDestination, newWeight);
    QCOMPARE(spyEdited.count(), 1);
    QCOMPARE(agent->getBegining(), newBegining);
    QCOMPARE(agent->getDestination(), newDestination);
    QCOMPARE(agent->getWeight(), newWeight);
    QCOMPARE(spyDeleted.count(), 0);
    delete agent;
    QCOMPARE(spyDeleted.count(), 1);
    QCOMPARE(spyEdited.count(), 1);
}

void AgentTest::jsonTest() {
    QString begining = "Kraków";
    QString destination = "Warszawa";
    double weight = 2.15;
    QJsonObject comparableJson;
    comparableJson["begining"] = begining;
    comparableJson["destination"] = destination;
    comparableJson["weight"] = weight;
    Agent agent(begining, destination, weight);
    QCOMPARE(agent.tojSON(), comparableJson);
}

QTEST_APPLESS_MAIN(AgentTest)

#include "tst_agenttest.moc"
