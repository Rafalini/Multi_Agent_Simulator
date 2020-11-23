#include <QtTest>

// add necessary includes here

class AgentsTests : public QObject
{
    Q_OBJECT

public:
    AgentsTests();
    ~AgentsTests();

private slots:
    void test_case1();

};

AgentsTests::AgentsTests()
{

}

AgentsTests::~AgentsTests()
{

}

void AgentsTests::test_case1()
{

}

QTEST_APPLESS_MAIN(AgentsTests)

#include "tst_agentstests.moc"
